#include <sec_email.h>

#ifndef JJ_SECURITY_EMAIL 
auto constexpr DEFAULT_SEC_EMAIL = "security@email.com";
#else
auto constexpr DEFAULT_SEC_EMAIL = #JJ_SECURITY_EMAIL;
#endif


namespace jj::sec {

    namespace
    {
        Address const SECURITY_ADDRESS{DEFAULT_SEC_EMAIL};
    }

    auto address() -> Address const& {
        return SECURITY_ADDRESS;
    }

} // namespace jj::sec

