#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <limits>
#include <string>

#include "matrix.hpp"

using std::cout, std::cerr, std::endl;
using std::vector;
using std::string;

// sum halfs of substrings are equal

int max_sub_str_len(string const& str) {

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

int max_sub_str_len_DP(string const& str) {
    
    auto const n = str.size();
    matrix<unsigned> sum(n, n);
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


int main() {

    string s = "124142";

    cout << max_sub_str_len(s) << endl;
    cout << max_sub_str_len_DP(s) << endl;

    s = "9430723";
     cout << max_sub_str_len(s) << endl;
     cout << max_sub_str_len_DP(s) << endl;
}

