#ifndef JJ_SEC_PATTERNS_H_
#define JJ_SEC_PATTERNS_H_

#include <message.h>
#include <address.h>

namespace jj::sec {

    [[nodiscard]] auto is_suspicious(jj::Message const& msg) -> bool;
    [[nodiscard]] auto address() -> Address const&;


}
#endif  // JJ_SEC_PATTERNS_H_
