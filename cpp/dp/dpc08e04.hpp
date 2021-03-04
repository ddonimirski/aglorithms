#if !defined DP_CH08_E04
#define DP_CH08_E04

#include <vector>
#include <algorithm>
#include <limits>

#include "utils/matrix.hpp"

//TODO:: separate header

namespace dp::ch08::e01
{
    auto minPathCost(int m, int n, utils::matrix_int const& cost) -> int
    {
        if (m == 0 && n == 0) return cost[m][n];
        if (m == 0) return minPathCost(m, n - 1, cost) + cost[m][n];
        if (n == 0) return minPathCost(m - 1, n, cost) + cost[m][n];

        auto const x = minPathCost(m - 1, n, cost);
        auto const y = minPathCost(m, n - 1, cost);
        return std::min(x, y) + cost[m][n];
    }
}

namespace dp::ch08::e03
{
    auto minPathCost_impl(int m, int n, utils::matrix_int const& cost, utils::matrix_int const& memo) -> int
    {
        if (memo[m][n] != 0)
        {
            return memo[m][n]; // 
        }

        if (m == 0 && n == 0)
        {
            memo[m][n] = cost[m][n];
        }
        else if (m == 0)
        {
            memo[m][n] = minPathCost_impl(m, n - 1, cost, memo) + cost[m][n];
        }
        else if (n == 0)
        {
            memo[m][n] = minPathCost_impl(m - 1, n, cost, memo) + cost[m][n];
        }
        else
        {
            auto const x = minPathCost_impl(m - 1, n, cost, memo);
            auto const y = minPathCost_impl(m, n - 1, cost, memo);
            memo[m][n] = std::min(x, y) + cost[m][n];
        }

        return memo[m][n];
    }

    auto minPathCost(int m, int n, utils::matrix_int const& cost)
    {
        utils::matrix_int memo(m+1, n+1);
        auto const ret =  minPathCost_impl(m, n, cost, memo);
        return ret;
    }
}


namespace dp::ch08::e04
{
    auto minPathCost(int m, int n, utils::matrix_int const& cost) -> int
    {
        utils::matrix_int memo(m+1, n+1);

        memo[0][0] = cost[0][0];

        for (auto c = 1; c <= n; ++c)
        {
            memo[0][c] = memo[0][c-1] + cost[0][c];
        }

        for (auto r = 0; r <= m; ++r)
        {
            memo[r][0] = memo[r-1][0] + cost[r][0];
        }

        for (auto r = 1; r <= m; ++r)
        {
            for (auto c = 1; c <= n; ++c)
            {
                memo[r][c] = std::min(memo[r-1][c], memo[r][c-1]) + cost[r][c];
            }
        }

        return memo[m][n];
    }
}

#endif // DP_CH08_E04
