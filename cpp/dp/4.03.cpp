#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <limits>

#include "matrix.hpp"

using std::cout, std::cerr, std::endl;
using std::vector;
using std::min;

matrix<int> cost(4, 4);
matrix<int> m(4, 4);

auto calculate_min_cost(int s, int d) {
    if (s == d || s == d-1) return cost[s][d];
    if (m[s][d] == 0) {
        auto min_cost = cost[s][d];
        for (int i = s+1; i < d; ++i) {
            auto const t1 = calculate_min_cost(s, i);
            auto const t2 = calculate_min_cost(i, d);
            auto const tmp = t1 + t2;
            if (tmp < min_cost) min_cost = tmp;
        }
        m[s][d] = min_cost;
    }

    return m[s][d];
}


int main() {

    for (int r = 0; r < m.__row_size; ++r) {
            cost[r][r] = 0;
    }
    // tickes price
    cost[0][1] = 10;
    cost[0][2] = 75;
    cost[0][3] = 94;
    cost[1][2] = 35;
    cost[1][3] = 50;
    cost[2][3] = 80;

    auto const r = calculate_min_cost(0, 4-1);
    cout << "min cost: " << r << endl;

    cout << m << endl;
}

