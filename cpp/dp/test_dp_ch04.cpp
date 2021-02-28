#include "dpc04e02.hpp"

#include "gtest/gtest.h"
#include "utils/test.hpp"
#include "utils/pr.hpp"
#include "utils/costfun.hpp"
#include "utils/scopetimer.hpp"

#include <iostream>
using std::cout;

using namespace dp::ch04;

TEST(dpch04e02, min_dist)
{
    // TODO: add time tests

    {
        constexpr auto n = 7;
        constexpr auto s = 0;
        constexpr auto d = n-1;
        auto cost = utils::costFun<n, 1244>;

        EXPECT_EQ(e02::minCost(s, d, cost), 87);
        EXPECT_EQ(e02::minCost(s, s, cost), 0);
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

        EXPECT_EQ(e02::minCost(s, d, cost), 60);
        EXPECT_EQ(e02::minCost(s, s, cost), 0);
        EXPECT_EQ(e02::minCost(s, s+1, cost), 10);
    }
}


TEST(dpch04e02, time_scope)
{
    constexpr auto n = 15;
    constexpr auto s = 0;
    constexpr auto d = n-1;
    auto const exp = 8;
    auto cost = utils::costFun<n, 1244>;
    cost(0,0); // to create costs

    auto check_time_execution = [&](){
        utils::scope_timer st(__func__, cout);
        return  e02::minCost(s, d, cost);
    };

    // n == 400, at about 5 ms   - dp::ch06::e03::minCost - DP top - down 
    // n == 400, at about 512 ms - dp::ch05::e02::minCost - recurence with memo 
    // n ==  15, at about 134 ms - dp::ch04::e02::minCost - recurence without memo 

    cout << "n = " << n << ' ';
    auto const res = check_time_execution();
    EXPECT_EQ(res , exp);
}
