#include <gtest/gtest.h>
#include <sec_email.h>
#include <utils.h>
#include <sstream>

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

TEST(test_Address, ostream_operator)
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
        std::stringstream ss;
        ss << addresses[i];
        ASSERT_EQ(ss.str(), to_str(expected[i]));
    }
}


TEST(test_Address, operator_equality)
{
    using namespace jj;

    Address const add1{"john.nash@example.com"};
    Address const add2{"john@example.com"};

    ASSERT_EQ(add1, add1);
    ASSERT_EQ(add2, add2);
    ASSERT_NE(add1, add2);
}

TEST(test_Address, hash)
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
        ASSERT_EQ(std::hash<Address>{}(addresses[i]), std::hash<std::string>{}(expected[i]));
    }
}
