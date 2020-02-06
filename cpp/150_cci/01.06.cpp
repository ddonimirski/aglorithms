#include <iostream>
#include <vector>
#include <cassert>

#include "matrix.hpp"

using std::cout, std::cerr , std::endl;
using std::cin;

//     i,j    <-     j, n-1-i
//      ^             |
//      |             v
// n-1-j, i   -> n-1-i, n-1-j
//
template<class T>
void rotate_right(matrix<T>& m) {

    auto N = m.__col_size;
    for (int layer = 0; layer < N/2; ++layer) {
        auto first = layer;
        auto last = N - 1 - layer;
        for (int i = first; i < last; ++i)
        {
            auto const offset = i - first;
            auto const tmp = m[first][i];
            m[first][i] = m[last-offset][first];
            m[last-offset][first] = m[last][last-offset];
            m[last][last-offset] = m[i][last];
            m[i][last] = tmp;
        }
    }
}

template<class T>
void rotate_left(matrix<T>& m) {

    auto const N = m.__col_size;
    for (auto j = 0; j < N/2; ++j) {
        auto const last = N - 1 - j;
        for (auto i = j; i < last; ++i) {

            auto const tmp = m[i][j];
            m[i][j] = m[j][N-1-i];
            m[j][N-1-i] = m[N-1-i][N-1-j];
            m[N-1-i][N-1-j] = m[N-1-j][i];
            m[N-1-j][i] = tmp;

        }
    }

}

int main() {

    unsigned N;
    cin  >> N;

    matrix<uint32_t> mm(N, N);

    for (int i = 0, c = 1; i < N; ++i)
        for (int j = 0; j < N; ++j)
            mm[i][j] = c++;

    cout << mm << endl;

    rotate_right(mm);

    cout << mm << endl;

    rotate_left(mm);

    cout << mm << endl;
}
