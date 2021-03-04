#include "dpc08e04.hpp"
#include "dpc08e05.hpp"

#include "gtest/gtest.h"
#include "utils/test.hpp"
#include "utils/pr.hpp"
#include "utils/scopetimer.hpp"
#include "utils/matrix.hpp"

#include <iostream>
using std::cout;

using namespace dp::ch08;


TEST(dpch08e01, min_path_cost)
{
    int conts_arr[] = { 1, 3, 5, 8, 4, 2, 1, 7, 4, 3, 2, 3};
    constexpr auto m = 3;
    constexpr auto n = 4;
    constexpr auto exp = 12;

    utils::matrix costs(conts_arr, m, n);

    auto res = CHECK_TIME(cout, e01::minPathCost, m-1, n-1, std::cref(costs));

    EXPECT_EQ(res, exp);

}

TEST(dpch08e03, min_path_cost)
{
    int conts_arr[] = { 1, 3, 5, 8, 4, 2, 1, 7, 4, 3, 2, 3};
    constexpr auto m = 3;
    constexpr auto n = 4;
    constexpr auto exp = 12;

    utils::matrix costs(conts_arr, m, n);

    auto res = CHECK_TIME(cout, e03::minPathCost, m-1, n-1, std::cref(costs));

    EXPECT_EQ(res, exp);

}

TEST(dpch08e04, min_path_cost)
{
    int conts_arr[] = { 1, 3, 5, 8, 4, 2, 1, 7, 4, 3, 2, 3};
    constexpr auto m = 3;
    constexpr auto n = 4;
    constexpr auto exp = 12;

    utils::matrix costs(conts_arr, m, n);

    auto res = CHECK_TIME(cout, e04::minPathCost, m-1, n-1, std::cref(costs));

    EXPECT_EQ(res, exp);

}

TEST(dpch08e05, count_ways)
{
    constexpr auto n = 5;
    constexpr auto exp = 8;

    auto const res = CHECK_TIME(cout, e05::countWays, n);
    EXPECT_EQ(res, exp);
}
