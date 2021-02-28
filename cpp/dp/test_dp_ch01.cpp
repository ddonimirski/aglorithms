#include "dpc01e01.hpp"
#include "dpc01e06.hpp"
#include "dpc01e07.hpp"
#include "dpc01e12.hpp"

#include "gtest/gtest.h"
#include "utils/test.hpp"
#include "utils/pr.hpp"

#include <algorithm>
#include <numeric>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

using std::cerr, std::cout, std::endl;

using namespace dp::ch01;

TEST(dp_ch01_e01, sum)
{
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7 };

    auto const expected = std::accumulate(v.begin(), v.end(), 0);
    auto const result = e01::sum(v);
    ASSERT_EQ(expected, result);
}


TEST(dp_ch01_e06, tower_of_hanoi)
{
    std::stringstream ss;
    e06::towerOfHanoi(ss, 's', 'd', 'e', 3);

    std::string const exp =
        "move disk 1 from s to d\n"
        "move disk 2 from s to e\n"
        "move disk 1 from d to e\n"
        "move disk 3 from s to d\n"
        "move disk 1 from e to s\n"
        "move disk 2 from e to d\n"
        "move disk 1 from s to d\n";

    ASSERT_EQ(ss.str(), exp);
}


TEST(dp_ch01_e07, tail_head)
{
    auto head = std::make_shared<e07::node>(0);
    for (int i = 1; i < 10; ++i) {
        auto tmp = std::make_shared<e07::node>(i);
        tmp->next = head;
        head = tmp;
    }

    {
        std::string const s1 =
            "0\n"
            "1\n"
            "2\n"
            "3\n"
            "4\n"
            "5\n"
            "6\n"
            "7\n"
            "8\n"
            "9\n";

        std::stringstream ss;
        e07::traversa1(ss, head);
        EXPECT_EQ(ss.str(), s1);
    }

    {
        std::string const s2 =
            "9\n"
            "8\n"
            "7\n"
            "6\n"
            "5\n"
            "4\n"
            "3\n"
            "2\n"
            "1\n"
            "0\n";

        std::stringstream ss;
        e07::traversa2(ss, head);
        EXPECT_EQ(ss.str(), s2);
    }
}

TEST(dp_ch01_e12, bubble_sort)
{
    std::vector const exp = {8, 7, 6, 5, 4, 3, 2, 1, 0};
    std::vector v = { 5, 1, 6, 7, 8, 2, 3, 0, 4};

    e12::bubble_sort(v);
    EXPECT_ITERABLE_EQ(exp, v);

    v = { 5, 1, 6, 7, 8, 2, 3, 0, 4};
    e12::bubble_sort_rec(v);
    EXPECT_ITERABLE_EQ(exp, v);
}

