#include <manager.h>
#include <address.h>
#include <unordered_map>
#include <set>
#include <memory>
#include <queue.h>
#include <thread>
#include <sec_email.h>
#include <log.h>

#include <iostream>


namespace jj {

    void Manager::create_account(AccountConf&& conf) {

         auto const address = conf.address_;
 
         if (map_.find(address) == map_.end())
         {
             LOG_DBG("create account for ", address);

             auto new_queue = std::make_shared<Queue<QueueItem>>();
             conf.queue_ = new_queue;

             if (!conf.sender_) {
                 conf.sender_ = [this](Message&& msg) {
                     send_to(std::move(msg));
                 };
             }

             auto new_account = Account::create(std::move(conf));

             auto thread_runner = [account = new_account]() {
                    LOG_DBG("start runner ", account->conf_.address_);
                    while(true) {
                        account->receive_item_from_queue();
                    }
                    LOG_DBG("end runner ", account->conf_.address_);
             };

             map_.emplace(
                     address,
                     Item {
                        .account_ = new_account,
                        .thread_ = std::thread(thread_runner)
                    });

             map_.at(address).thread_.detach(); // TODO consider join and the Manager destruction ?
         }
    }

    // function add pattern to all actors
    void Manager::notify_pattern(std::string const& pattern) {
        for (auto & [address, item]: map_) {
            if (address == sec::address()) {
                continue;
            }
            item.account_->push_to_queue(Pattern{.pattern_ = pattern});
        }
    }

    void Manager::notify_blocked(std::string const& pattern) {
        for (auto & [address, item]: map_) {
            if (address == sec::address()) {
                continue;
            }
            item.account_->push_to_queue(Blocked{.address_ = Address(pattern)});
        }
    }

    void Manager::send_to(Message&& msg) {

        auto const address = msg.address_;

        if (auto item = map_.find(address); item != map_.end()) {
            LOG_DBG("push ", msg);
            item->second.account_->push_to_queue(std::move(msg));
        }
        else {
            LOG_DBG("account with address ", msg.address_, " doesn't exist");

            auto sender = [this](Message&& msg) { send_to(std::move(msg)); };

            create_account(AccountConf{ .address_ = address, .sender_ = sender});

            map_.at(address).account_->push_to_queue(std::move(msg));
        }
    }
}

