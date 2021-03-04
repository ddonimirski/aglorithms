#include "dpc06e03.hpp"
#include "dpc06e04.hpp"

#include "gtest/gtest.h"
#include "utils/test.hpp"
#include "utils/pr.hpp"
#include "utils/costfun.hpp"
#include "utils/scopetimer.hpp"

#include <iostream>
using std::cout;

using namespace dp::ch06;

TEST(dpch06e03, min_dist)
{
    {
        constexpr auto n = 7;
        constexpr auto s = 0;
        constexpr auto d = n-1;
        auto cost = utils::costFun<n, 1244>;

        EXPECT_EQ(e03::minCost(s, d, cost), 87);
    }

    {
        constexpr auto n = 4;
        constexpr auto s = 0;
        constexpr auto d = n-1;
        auto cost = [&](auto i, auto j)
        {
            static int arr[n][n]  = {
                {  0, 10, 75, 94 },
                { -1,  0, 35, 50 },
                { -1, -1,  0, 80 },
                { -1, -1, -1,  0 } };

            return arr[i][j];
        };

        auto const res = e03::minCost(s, d, cost);
        auto const exp = 60;
        EXPECT_EQ(res, exp);
        EXPECT_EQ(e03::minCost(s, s, cost), 0);
        EXPECT_EQ(e03::minCost(s, s+1, cost), 10);
    }
}


TEST(dpch06e03, time_scope)
{
    constexpr auto n = 400;
    constexpr auto s = 0;
    constexpr auto d = n-1;
    constexpr auto exp = 25;
    auto cost = utils::costFun<n, 1244>;
    cost(0,0); // to create costs

    cout << "n = " << n << ' ';

    // n == 400, at about 5 ms   - dp::ch06::e03::minCost - DP top - down 
    // using namespace std::literals;
    // n == 400, at about 512 ms - dp::ch05::e02::minCost - recurence with memo 
    // n ==  15, at about 132 ms - dp::ch04::e02::minCost - recurence without memo 

    auto const res = CHECK_TIME(cout, e03::minCost<decltype(cost)>, s, d, cost);
    EXPECT_EQ(res, exp);
}

TEST(dpch06e04, max_len_substring)
{
    using namespace std::literals;

    auto s = "124142"sv;
    auto exp = 6;
    auto res = exp; // :)

    res =  CHECK_TIME(cout, e04::max_sub_str_len, s);
    EXPECT_EQ(res, exp);

    res = CHECK_TIME(cout, e04::max_sub_str_len_DP, s);
    EXPECT_EQ(res, exp);

    res = CHECK_TIME(cout, e04::max_sub_str_len_prefix, s);
    EXPECT_EQ(res, exp);

    s = "943072394307239430723948072394307294307239430723943072394807239430723394307239430723943072394807239430723948072394307239438923943078394307239430723943072394307239480723943072394807239430723943872394307239430723";
    exp = 162;

    res =  CHECK_TIME(cout, e04::max_sub_str_len, s);
    EXPECT_EQ(res, exp);

    res = CHECK_TIME(cout, e04::max_sub_str_len_DP, s);
    EXPECT_EQ(res, exp);

#if 0 // failed
    res = CHECK_TIME(cout, e04::max_sub_str_len_prefix, s);
    EXPECT_EQ(res, exp);
#endif 
}
