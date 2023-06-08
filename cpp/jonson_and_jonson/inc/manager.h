#ifndef JJ_MANAGER_H_
#define JJ_MANAGER_H_

#include <account.h>
#include <string>
#include <account_conf.h>
#include <address.h>
#include <unordered_map>
#include <set>
#include <memory>
#include <queue.h>
#include <thread>
#include <sec_email.h>
#include <log.h>

namespace jj {

        struct Manager final {

            struct Item {
                std::shared_ptr<Account> account_;
                std::thread thread_;
            };


            std::unordered_map<Address, Item> map_ = {};

            Manager() {
                // create security account
                create_account(AccountConf{ .address_ = sec::address(), .sender_ = [this](Message&& msg) { send_to(std::move(msg)); } });
            }

            void create_account(AccountConf&& conf);

            void notify_pattern(std::string const& pattern);

            void notify_blocked(std::string const& pattern);

            void send_to(Message&& msg);

        };

} // namespace jj {

#endif // JJ_MANAGER_H_
