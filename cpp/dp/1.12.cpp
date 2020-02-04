#include <iostream>
#include <vector>
#include <cassert>

using std::cout, std::cerr, std::endl;
using std::vector;

// bubble_sort
//
//

template<class T>
void swap_int(T& v1, T& v2) {
    v1 ^= v2;
    v2 ^= v1;
    v1 ^= v2;
}

template<class T, template<typename...> class C>
void bubble_sort(C<T>& c) {
    for (int i = 0; i < c.size(); ++i) {
        for (int j = 0; j < c.size()-1; ++j) {
            if (c[j] < c[j+1])
                swap_int(c[j], c[j+1]);
        }
    }
}


template<class T, template<typename...> class C>
void bubble_sort_rec(C<T>& c, size_t n) {
    if (n == 0) return;
    for (size_t j = 0; j < n-1; ++j) {
        if (c[j] < c[j+1])
            swap_int(c[j], c[j+1]);
    }
    bubble_sort_rec(c, n-1);
}

template<class T, template<typename...> class C>
void bubble_sort_rec(C<T>& c) {
    bubble_sort_rec(c, c.size()-1);
}

template<class C>
void pr(C const& c) {
    for (auto v: c) {
        cout << v << ' ';
    }
    cout << '\n';
}


int main() {

    vector v = { 5, 1, 6, 7, 8, 2, 3, 0, 4};

    pr(v);
    bubble_sort(v);
    pr(v);

    v = { 5, 1, 6, 7, 8, 2, 3, 0, 4};
    pr(v);
    bubble_sort_rec(v);
    pr(v);
}
