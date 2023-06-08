#include <manager.h>
#include <address.h>
#include <unordered_map>
#include <set>
#include <memory>
#include <queue.h>
#include <thread>
#include <sec_email.h>
#include <log.h>


namespace jj {

    struct Item {
        std::shared_ptr<Account> account_;
        std::thread thread_;
        std::shared_ptr<Queue<Message>> queue_ = {};
    };


    namespace {

        struct Manager final {

            std::unordered_map<Address, Item> map_ = {};

            std::vector<std::string> patterns_ = {};
            std::set<Address> blocked_ = {};

            Manager() {
             create_account(AccountConf{ .address_ = sec::address() });
            }
        };

        // NOLINTBEGIN
        Manager manager_{ };
        // NOLINTEND

    }

    void create_account(AccountConf&& conf) {

         auto& map = manager_.map_;
         auto address = conf.address_;
 
         if (map.find(address) == map.end())
         {
             LOG_DBG("create account for ", address);
             auto new_account = Account::create(std::move(conf));
             auto new_queue = std::make_shared<Queue<Message>>();
             map.emplace(
                     address,
                     Item {
                     .account_ =  new_account,
                     .thread_ = std::thread([new_account, new_queue]() {
                                while(true) {
                                    auto msg = new_queue->pop();
                                    LOG_DBG("thread pop ", msg);
                                    new_account->receive(std::move(msg));
                                }
                             }),
                     .queue_ = new_queue
                });

             map.at(address).thread_.detach();
         }
    }

    void notify_pattern(std::string const& pattern) {
        // TODO implement
        (void)pattern;
    }

    void send_to(Message&& msg) {

        auto& map = manager_.map_;

        if (auto item = map.find(msg.address_); item != map.end()) {
            LOG_DBG("push ", msg);
            item->second.queue_->push(std::move(msg));
            return;
        }

        LOG_DBG("address ", msg.address_, " doesn't exist");

        create_account(AccountConf{ .address_ = msg.address_, .send_ = send_to });

        map.at(msg.address_).queue_->push(std::move(msg));
    }
}

