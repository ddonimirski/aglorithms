#if !defined AL_150_CCI_C01_E06
#define AL_150_CCI_C01_E06

#include <utils/matrix.hpp>

namespace a150_cci::c01::e06
{

//     i,j    <-     j, n-1-i
//      ^             |
//      |             v
// n-1-j, i   -> n-1-i, n-1-j
//
template<class T>
void rotate_right(utils::matrix<T>& m) {

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
void rotate_left(utils::matrix<T>& m) {

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
} //  namespace a150_cci::c01::e06

#endif // AL_150_CCI_C01_E06

