#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <limits>
#include <cstring>

#include "matrix.hpp"

using std::cout, std::cerr, std::endl;
using std::cin;
using std::vector;

int const conts_arr[] = { 1, 3, 5, 8, 4, 2, 1, 7, 4, 3, 2, 3};

matrix costs(conts_arr, 3, 4);
matrix<int> mm(3, 4);

constexpr auto MAXINT = std::numeric_limits<int>::max();

int cc(int i, int j) {

    if (mm[i][j] == MAXINT) {
        auto sum1 = MAXINT;
        auto sum2 = MAXINT;

        if (i != 0)
            sum1 = cc(i-1, j) + costs[i][j];
        else if (i == 0)
            sum1 = costs[i][j];

        if (j != 0)
            sum2 = cc(i, j-1) + costs[i][j];
        else if (j == 0)
            sum2 = costs[i][j];

        cerr << i << ' ' << j << endl;
        mm[i][j] = std::min(sum1, sum2);
    }

    return mm[i][j];
}

int cc(matrix<int const> const& c) {

    //matrix<int> mm(c.__row_size+1, c.__col_size+1);
    //for (size_t i = 1; i < mm.__row_size; ++i) {
    //    for (size_t j = 1; j < mm.__col_size; ++j) {
    //        mm[i][j] = std::min(mm[i-1][j], mm[i][j-1]) + c[i-1][j-1];
    //    }
    //}
    //
    //cerr << mm << endl;
    //return mm[c.__row_size][c.__col_size];
    
    matrix<int> mm(c.__row_size, c.__col_size);

    mm[0][0] = c[0][0];
    for (int i=1; i<mm.__col_size; ++i)
        mm[0][i] = c[0][i];

    for (int i=1; i<c.__row_size; ++i)
        mm[i][0] = c[i][0];

    for (size_t i = 1; i < mm.__row_size; ++i) {
        for (size_t j = 1; j < mm.__col_size; ++j) {
            mm[i][j] = std::min(mm[i-1][j], mm[i][j-1]) + c[i][j];
        }
    }
    
    cerr << mm << endl;
    return mm[c.__row_size-1][c.__col_size-1];
}


int main() {

    cout << costs << endl;

    for (int r=0; r < mm.__row_size; ++r)
        for (int c=0; c < mm.__col_size; ++c)
            mm[r][c] = MAXINT;


    cout << cc(3-1, 4-1) << endl;
    cout << mm << endl;
    cout << cc(costs) << endl;



}
