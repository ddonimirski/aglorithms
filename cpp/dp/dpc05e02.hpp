#if !defined DP_CH05_E02
#define DP_CH05_E02

// recurrence computation with memoization

#include <limits>

#include "utils/pr.hpp"
#include "utils/matrix.hpp"

namespace dp::ch05::e02
{
    template<class FUN>
    auto minCost_impl(int s, int d, utils::matrix_int& memo, FUN cost) -> long long
    {
        if (s == d || s == d-1) return cost(s, d);

        if (memo[s][d] == 0)
        {
            auto min_cost = cost(s, d);

            for (auto i = s + 1; i < d; ++i)
            {
                if (auto const tmp = minCost_impl(s, i, memo, cost) + minCost_impl(i, d, memo, cost); tmp < min_cost)
                {
                    min_cost = tmp;
                }
            }

            memo[s][d] = min_cost;
        }

        return memo[s][d];
    }

    template<class FUN>
    auto minCost(size_t s, size_t d, FUN cost)
    {
#if PRINT_COST
        for (int i = s; i <= d; ++i)
        {
            std::cerr << '[';
            for (int j = s; j <= d; ++j)
            {
                std::cerr << cost(i, j) << ' ';
            }
            std::cerr << ']' << '\n';
        }
#endif // PRINT_COST

        utils::matrix_int memo(d+1);
        return minCost_impl(s, d, memo, cost);
    }

} // namespace dp::ch05::e02

#endif // DP_CH05_E02
