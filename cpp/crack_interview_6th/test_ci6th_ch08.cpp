#include "c08e01.hpp"

#include "gtest/gtest.h"

#include <iostream>

using std::cout, std::endl;

using namespace ci6th::ch08;


TEST(ci6th_ch08_e01, tripe_step)
{
    using value_type = e01::value_type;

    auto triple_step = [](value_type steps) -> value_type
    {
        std::vector<e01::value_type> mem = {0, 1};
        value_type const sum = e01::triple_step_rec(steps, mem);
        assert(sum == e01::triple_step_int(steps));
        assert(sum == e01::triple_step_int2(steps));
        return sum;
    };


    ASSERT_EQ(2, triple_step(2));
    ASSERT_EQ(4, triple_step(3));
    ASSERT_EQ(7, triple_step(4));
    ASSERT_EQ(13, triple_step(5));
    ASSERT_EQ(24, triple_step(6));
    ASSERT_EQ(44, triple_step(7));
    ASSERT_EQ(81, triple_step(8));
    ASSERT_EQ(149, triple_step(9));
    ASSERT_EQ(274, triple_step(10));
}

