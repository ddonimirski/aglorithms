#if !defined DP_CH04_E02
#define DP_CH04_E02

// recurrence computation with no memoization

#include <limits>
#include <functional>

#include "utils/pr.hpp"

namespace dp::ch04::e02
{
    template<class FUN>
    auto minCost(int s, int d, FUN cost) -> long long
    {
        auto min_cost = cost(s, d);

        if (s != d && s != d-1)
        {
            for (auto i = s + 1; i < d; ++i)
            {
                if (auto const tmp = minCost(s, i, cost) + minCost(i, d, cost); tmp < min_cost)
                {
                    min_cost = tmp;
                }
            }
        }

        return min_cost;
    }

} // namespace dp::ch04::e02

#endif // DP_CH04_E02



