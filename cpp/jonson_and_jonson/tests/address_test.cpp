#include <gtest/gtest.h>
#include <sec_email.h>
#include <utils.h>

TEST(test_Address, to_str)
{
    using namespace jj;

    Address const addresses[] = {
        sec::address(),
        "john.nash@example.com"
    };

    std::string const expected[] {
        to_str(sec::address()),
        std::string("john.nash@example.com")
    };

    for (int i = 0; i < size(addresses); ++i) {
        ASSERT_EQ(addresses[i], expected[i]);
    }
}
