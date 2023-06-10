#include <gtest/gtest.h>
#include <sec_email.h>
#include <utils.h>

#ifndef JJ_SECURITY_EMAIL 
auto constexpr DEFAULT_SEC_EMAIL = "security@email.com";
#else
auto constexpr DEFAULT_SEC_EMAIL = #JJ_SECURITY_EMAIL;
#endif

TEST(test_SecEmail, check_sec_address_value)
{
    auto const expected = jj::Address{DEFAULT_SEC_EMAIL};
    ASSERT_EQ(expected, jj::sec::address());
}
