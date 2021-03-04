#if !defined DP_CH06_04
#define DP_CH06_04

#include <iostream>

#include <string_view>
#include <vector>

#include "utils/matrix.hpp"

namespace dp::ch06::e04
{

// sum halfs of substrings are equal

int max_sub_str_len(std::string_view str)
{
    // Time O(n^3) Space O(1)
    auto n = str.size();
    auto max_len = 0u;

    for (auto i = 0u; i < n; ++i) {
        for (auto j = i + 1u; j < n; j += 2) {

            auto len = j - i + 1;
            if (max_len >= len) continue;

            auto const half = len/2;
            int lsum = 0, rsum = 0;
            for (auto k = 0u; k < half; ++k ) {
                lsum += str[i+k] - '0';
                rsum += str[i+k+half] - '0';
            }

            if (lsum == rsum) max_len = len;
        }
    }

    return max_len;
}

// code .06.05
int max_sub_str_len_DP(std::string_view str)
{
    // Time O(n^2) Space O(n^2)
    auto const n = str.size();
    utils::matrix<unsigned> sum(n);
    auto max_len = 0u;

    for (auto i = 0u; i < n ; ++i) {
        sum[i][i] = str[i] - '0';
    }

    for (auto len = 2u; len <= n; ++len) {

        for (auto i = 0u; i < n-len+1; ++i) {
            auto const j = i+len-1;
            auto const k = len/2;
            sum[i][j] = sum[i][j-k] + sum[j-k+1][j];

            if (len%2 == 0 && sum[i][j-k] == sum[j-k+1][j] && len > max_len) {
                max_len = len;
            }
        }
    }

    return max_len;
}

// additional solution
int max_sub_str_len_prefix(std::string_view str)
{
    // Time O(n^2) Space O(n)
    auto const n = str.size();
    std::vector<unsigned> sums(str.size()+1, 0);
    auto max_len = 0u;

    for (auto i = 0u; i < n; ++i)
    {
        for (auto j = i + 1u; j < n; j += 2)
        {
            auto len = j - i + 1;
            if (max_len >= len) continue;
            auto const half = len/2;
            auto const lsum = sums[i+half] - sums[i];
            auto const rsum = sums[i+len] - sums[i+half];

            if (lsum == rsum) max_len = len;
        }
    }

    return max_len;
}

} // namespace dp::ch06::e04

#endif // DP_CH06_04
