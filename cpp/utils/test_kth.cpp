#include <iostream>
#include <vector>
using std::cout, std::endl, std::cerr;
using std::vector;

#include "kth.hpp"

int main() {
    int a[] = {1, 2, 4, 5, 8};
    int b[] = {3, 6, 7};

    auto const al = sizeof(a)/sizeof(*a);
    auto const bl = sizeof(b)/sizeof(*b);

    for (auto i = 0u; i < al+bl; ++i)
        cout << kth_rec(i, a, a+al, b, b+bl) << endl;

    for (auto i = 0u; i < al+bl; ++i)
        cout << kth_iter(i, a, a+al, b, b+bl) << endl;

    vector va = {1, 2, 4, 5, 8};
    vector vb = {3, 6, 7};

    for (auto i = 0u; i < al+bl; ++i)
        cout << kth_iter(i, va.begin(), va.end(), vb.begin(), vb.end()) << endl;
    
}
