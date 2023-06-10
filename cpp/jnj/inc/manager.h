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
#include <manager_item.h>

namespace jj {

        class Manager final {

            public:


            std::unordered_map<Address, std::shared_ptr<Item>> accounts_ = {};

            public:

            Manager();
            Manager(Manager&&) = delete;
            Manager(Manager const&) = delete;
            ~Manager();

            void create_account(AccountConf&& conf);

            void notify_pattern(std::string const& pattern);

            void broadcast_blocked(std::string const& pattern);

            void send_to(Message&& msg);

        };

} // namespace jj {

#endif // JJ_MANAGER_H_
