#ifndef JJ_QUQUE_ITEM_H_
#define JJ_QUQUE_ITEM_H_

#include <variant>
#include <message.h>
#include <address.h>

namespace jj {
    struct Blocked { Address address_; };
    
    struct Pattern { std::string pattern_; };

    using QueueItem = std::variant<Message, Blocked, Pattern>;
} // namespace jj {

#endif // JJ_QUQUE_ITEM_H_
