#if !defined UTILS_MATRIX_HPP
#define UTILS_MATRIX_HPP

#if !defined NO_STREAM
#include <iostream>
#endif

namespace utils
{

template<class T>
struct matrix {

    using value_type = T;

    value_type *const __storage;
    size_t __row_size;
    size_t __col_size;
    bool const __free_storage;

    matrix() = delete;
    matrix(value_type* m, size_t r, size_t c, bool fs = false):
        __storage(m), __row_size(r), __col_size(c), __free_storage(fs) {}
    matrix(size_t r, size_t c): matrix(new value_type[r*c], r, c, true) {}
    //TODO: consider as resove this in compile time
    ~matrix() { if (__free_storage) delete [] __storage; }

    value_type* get_row(size_t r) const noexcept { return __storage + (r * __col_size); }
    value_type* operator[](size_t r) noexcept { return get_row(r); }
    value_type* const operator[](size_t r) const noexcept { return get_row(r); }

#if !defined NO_STREAM
    friend  std::ostream& operator << (std::ostream& os, matrix const& m) {
        for (size_t r = 0; r < m.__row_size; ++r) {
            for (size_t c = 0; c < m.__col_size; ++c) {
                os << m[r][c] << ' ';
            }
            os << '\n';
        }
        return os;
    }
#endif 
};

} // namespace utils

#endif // UTILS_MATRIX_HPP
