#include <iostream>
#include <cassert>
#include "2.2.hpp"
#include <array>
#include <vector>

using std::vector;

template<class T>
using array_10 = std::array<T, 10>;


template<class C>
void pr(C const& c){
    for (auto const& v: c) {
        std::cout << v << ' ';
    }
    std::cout << '\n';
}

int main() {


    vector arr = {2,3,4,6,1,5,7,0,9,8};

    pr(arr);

    insertion_sort(arr);

    pr(arr);
}
