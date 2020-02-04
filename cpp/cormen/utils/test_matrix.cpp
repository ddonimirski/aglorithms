#include <cassert>
#include <iostream>

#include "matrix.hpp"

using std::cout, std::cerr, std::endl;

int main() {

    matrix<int> mm(10, 5);

    for (size_t r = 0, v = 0; r < mm.__row_size; ++r)
        for (size_t c = 0; c < mm.__col_size; ++c)
            mm[r][c] = ++v;

    cout << mm << endl;


}
