#include "dpc07e04.hpp"

#include "gtest/gtest.h"
#include "utils/test.hpp"
#include "utils/pr.hpp"
#include "utils/scopetimer.hpp"

#include <iostream>
using std::cout;

using namespace dp::ch07;

TEST(dpch07e04, combination)
{
    constexpr auto n = 32;
    constexpr auto m = 10;
    constexpr auto e = 64512240;
    auto r = e;

    r = CHECK_TIME(cout, e04::comb, n, m);
    EXPECT_EQ(r, e);

    r = CHECK_TIME(cout, e04::comb_memo, n, m);
    EXPECT_EQ(r, e);
}
