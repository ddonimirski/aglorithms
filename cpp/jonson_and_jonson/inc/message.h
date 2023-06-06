#ifndef JJ_MESSAGE_H_
#define JJ_MESSAGE_H_

#include <string>
#include <address.h>
#include <format>

namespace jj
{

struct Message
{
    Address address_;
    std::string body_;

    friend inline auto to_str(Message const& msg) -> std::string {
        return std::format("address: {}, body: {}", to_str(msg), msg.body_);
    }
};


} // namespace jj

#endif // JJ_MESSAGE_H_
