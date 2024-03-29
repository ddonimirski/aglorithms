#if !defined UTILS_MATRIX_HPP
#define UTILS_MATRIX_HPP

//#if !defined NO_STREAM
#include <iostream>
//#endif
//

namespace utils
{

template<class T, T value = T{}>
struct matrix {

    using value_type = T;

    value_type* __storage;
    size_t __row_size;
    size_t __col_size;
    bool __free_storage;

    matrix() = delete;
    matrix(value_type* m, size_t r, size_t c, bool fs = false, bool init = false):
        __storage(m), __row_size(r), __col_size(c), __free_storage(fs)
    {
        if (init)
        {
            auto* beg = __storage;
            auto* const end = beg + __row_size * __col_size;
            while (beg != end) *beg++ = value;
        }

        std::cout << "matrix " << r  << ' ' << c << '\n';
        for (int r = 0; r < __row_size; ++r)
        {
            for (int c = 0; c < __col_size; ++c)
            {
                std::cout << get_row(r)[c] << ' ';
            }
            std::cout << '\n';
        }
    }

    explicit matrix(size_t r, size_t c): matrix(new value_type[r*c], r, c, true, true) {}
    explicit matrix(size_t n): matrix(n ,n) {}

    matrix(matrix&& m): matrix(m.__storage, m.__row_size, m.__col_size, m.__free_storage)
    {
        m.__free_storage = false;
        m.__storage = nullptr;
    }

    //TODO: consider as resove this in compile time
    ~matrix()
    {
        if (__storage && __free_storage)
        {
            delete [] __storage;
        }
    }

    value_type* get_row(size_t r) const noexcept { return __storage + (r * __col_size); }
    value_type* operator[](size_t r) noexcept { return get_row(r); }
    value_type* const operator[](size_t r) const noexcept { return get_row(r); }

#if !defined NO_STREAM
    friend  std::ostream& operator << (std::ostream& os, matrix const& m) {
        for (size_t r = 0; r < m.__row_size; ++r) {
            os << '[';
            for (size_t c = 0; c < m.__col_size; ++c) {
                os << m[r][c] << ' ';
            }
            os << ']' << '\n';
        }
        return os;
    }
#endif 
};

using matrix_int = matrix<int>;

} // namespace utils

#endif // UTILS_MATRIX_HPP
