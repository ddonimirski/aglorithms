#if !defined DPC_CH07_04
#define DPC_CH07_04

#include <iostream>
#include <cassert>
#include <algorithm>
#include <limits>

#include "utils//matrix.hpp"


namespace dp::ch07::e04
{
// combination
int comb(int n, int m) {
    if (n == 0 || m == 0 || n == m)
        return 1;
    return comb(n-1, m) + comb(n-1, m-1);
}


int comb_memo_impl(int n, int m, utils::matrix_int& mm)
{
    if (n == 0 || m == 0 || n == m) return 1;

    if (mm[n][m] == 0)
    {
        mm[n][m] = comb_memo_impl(n-1, m, mm) + comb_memo_impl(n-1, m-1, mm);
    }

    return mm[n][m];
}

int comb_memo(int n, int m)
{
    utils::matrix_int mm(n,m);
    return comb_memo_impl(n, m, mm);
}

int comb_iter(int n, int m)
{
    return 0;
}

} // namespace dp::ch07::e04

#endif // DPC_CH07_04
