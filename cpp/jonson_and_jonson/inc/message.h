#ifndef JJ_MESSAGE_H_
#define JJ_MESSAGE_H_

#include <string>
#include <address.h>
#include <optional>
#include <ostream>

namespace jj
{
    struct Message final
    {
        Address address_;
        std::optional<Address> from_ = {};
        std::string body_;
    };


    [[nodiscard]] auto to_str(Message const& msg) -> std::string;

    auto operator << (std::ostream& os, Message const& msg) -> std::ostream&;

} // namespace jj

#endif // JJ_MESSAGE_H_
