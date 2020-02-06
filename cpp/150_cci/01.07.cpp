#include <iostream>
#include <vector>
#include <cassert>
#include <vector>

#include "matrix.hpp"

using std::cout, std::cerr , std::endl;
using std::cin;
using std::vector;

template<class T>
void set_zero(matrix<T>& m) {

    vector<bool> row(m.__row_size);
    vector<bool> col(m.__col_size);

    for (size_t r = 0; r < m.__row_size; ++r)
        for (size_t c = 0; c < m.__col_size; ++c)
            if (m[r][c] == 0)
                col[c] = row[r] = 1;


    for (size_t r = 0; r < m.__row_size; ++r)
        for (size_t c = 0; c < m.__col_size; ++c)
            if (col[c] || row[r])
                m[r][c] = 0;
}


int main() {

    int M, N;
    cin >> M >> N;

    matrix<int> mm(M, N);

    for (int i = 0, c = 1; i < mm.__row_size; ++i)
        for (int j = 0; j < mm.__col_size; ++j)
            mm[i][j] = c++;
    
    cin >> N;

    for (int i = 0; i < N; ++i) {
        int c, r;
        cin >> r >> c;

        mm[r][c] = 0;
    }

    cout << mm << endl;

    set_zero(mm);

    cout << mm << endl;
    
}
