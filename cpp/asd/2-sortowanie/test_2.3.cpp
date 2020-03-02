#include <iostream>
#include <cassert>
#include "2.3.hpp"
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
    //vector arr = {2,3};

    pr(arr);

    //quick_sort(arr);
    //quick_sort1(arr);
    //quick_sort2(arr);
    quick_sort3(arr);

    pr(arr);
}

