#ifndef JJ_ACCOUNT_CONF_H
#define JJ_ACCOUNT_CONF_H

#include <message.h>
#include <address.h>
#include <functional>
#include <queue.h>
#include <queue_item.h>
#include <memory>
#include <vector>
#include <unordered_set>

namespace jj {

    struct AccountConf
    {
        Address address_;
        std::shared_ptr<Queue<QueueItem>> queue_ = std::make_shared<Queue<QueueItem>>();
        std::function<void(Message&&)> sender_ = {};
        std::unordered_set<Address> blocked_address_ = {};
        std::vector<std::string> malware_patterns_ = {};
        std::vector<std::string> spam_patterns_ = { "discount", "inheritance", "lottery" };
    };

} // namespace jj {


#endif // JJ_ACCOUNT_CONF_H
