#include <gtest/gtest.h>
#include <utils.h>
#include <string>
//#include <iostream>

using namespace jj;

TEST(test_Utils, c_array_size)
{
    int arr[5];
    ASSERT_EQ(5, size(arr));
}

TEST(test_Utils, cypher_text)
{
    std::string const base = "abcde";
    std::string const expected = " #\"%$";
    ASSERT_EQ(expected, cypher_text(base, 0x41));
}

TEST(test_Utils, to_str)
{
    std::string const expected = "1053.4 hello";
    ASSERT_EQ(expected, to_str(std::hex, 16, 5, 3.4, " hello"));
}
