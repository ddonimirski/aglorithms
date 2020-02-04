#include <iostream>

using std::cout, std::cerr, std::endl;


template<class T>
struct matrix_view {

    using value_type = T;
    
    T* const _storage;

    size_t const row_size;
    size_t const col_size;


    matrix_view(T* s, size_t r, size_t c):
        _storage(s), row_size(r), col_size(c) { }

    T* get_row(int r) noexcept { return _storage + (r * col_size); }


    T* operator[](int r) { return get_row(r); }
    T const * operator[](int r) const { return get_row(r); }
};


int main() {

    int m [10*5];

    matrix_view mv(m, 10, 5);

    for (int i = 0, v = 0; i < 10; ++i) {
        for (int j = 0; j < 5; ++j) {
            mv[i][j] = ++v;
        }
    }

    
    for (int i = 0; i < 10*5; ++i) {
        cout << m[i]<< ' ';
        if ((i+1)%10 == 0) {
            cout << '\n';
        }
    }

}
