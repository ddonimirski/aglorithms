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
vector<int> minc(4);


template<class T> 
std::ostream& operator<< (std::ostream& os, vector<T> const& c) {
    for (auto const v: c) os << v << ' ';
    return os;
}

int calculate_min_cost() {
    minc[0] = 0;
    minc[1] = cost[0][1];

    for (int i = 2; i < 4; ++i) {
        minc[i] = cost[0][i];

        for (int j = 1; j < i; ++j) {
            auto const tmp = minc[j] + cost[j][i];
            if (minc[i] > tmp) {
                minc[i] = tmp;
            }
        }
    }

    return minc[4-1];
}


int main() {
    for (int r = 0; r < cost.__row_size; ++r) {
            cost[r][r] = 0;
    }
    // tickes price
    cost[0][1] = 10;
    cost[0][2] = 75;
    cost[0][3] = 94;
    cost[1][2] = 35;
    cost[1][3] = 50;
    cost[2][3] = 80;

    auto const r = calculate_min_cost();
    cout << "min cost: " << r << endl;
}
