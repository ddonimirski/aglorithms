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
 
         if (accounts_.find(address) == accounts_.end())
         {
             LOG_DBG("create account for ", address);
             accounts_.emplace(address, Item::create(std::move(conf)));
         }
         else {
            (void)std::move(conf);
         }
    }

    // function add pattern to all actors
    void Manager::notify_pattern(std::string const& pattern) {
        for (auto & [address, item]: accounts_) {
            if (address == sec::address()) {
                continue;
            }
            item->push_to_queue(Pattern{.pattern_ = pattern});
        }
    }

    // broadcast a blocked address
    void Manager::broadcast_blocked(std::string const& pattern) {
        for (auto & [address, item]: accounts_) {
            if (address == sec::address()) {
                continue;
            }
            item->push_to_queue(Blocked{.address_ = Address(pattern)});
        }
    }

    void Manager::send_to(Message&& msg) {

        auto const address = msg.address_;

        if (accounts_.find(address) == accounts_.end()) {
            LOG_DBG("account with address ", address, " doesn't exist");
            create_account(AccountConf{ .address_ = address });
        }

        LOG_DBG("push ", msg);
        accounts_.at(address)->push_to_queue(std::move(msg));
    }


    Manager::~Manager() {
        for (auto& [address, account]: accounts_) {
            LOG_DBG("stop request for ", address);
            account->stop();
        }
    }

    Manager::Manager() {
        // create security account
        create_account(AccountConf{ .address_ = sec::address() });
    }
}

