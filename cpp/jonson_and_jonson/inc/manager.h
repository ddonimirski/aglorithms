#ifndef JJ_MANAGER_H_
#define JJ_MANAGER_H_

#include <account.h>
#include <string>
#include <account_conf.h>

namespace jj {

    // [[nodiscard]] auto create_account(AccountConf&& conf) -> std::shared_ptr<Account>;
    void create_account(AccountConf&& conf);

    void notify_pattern(std::string const& pattern);

   // void send_to(Message&& msg);

} // namespace jj {

#endif // JJ_MANAGER_H_
