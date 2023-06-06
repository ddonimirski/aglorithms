#include <sec_patterns.h>


#ifndef JJ_SECURITY_EMAIL 
#define JJ_SECURITY_EMAIL "security@email.com"
#endif


namespace jj::sec {

    namespace
    {
        Address const SECURITY_ADDRESS{JJ_SECURITY_EMAIL};
    }


    [[nodiscard]] auto is_suspicious(jj::Message const& msg) -> bool {
        return false;
    }

    [[nodiscard]] auto address() -> Address const& {
        return SECURITY_ADDRESS;
    }
}

