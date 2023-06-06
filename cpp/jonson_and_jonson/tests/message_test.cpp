#include <gtest/gtest.h>
#include <sec_patterns.h>

TEST(test_Message, to_str)
{
    using namespace jj;

    Address const address[] = {
        sec::address(),
        "john.nash@example.com"
    };
}
