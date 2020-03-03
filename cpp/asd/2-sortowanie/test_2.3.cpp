#include <iostream>
#include <cassert>
#include "2.3.hpp"
#include <array>
#include <vector>
#include "pr.hpp"

using std::cerr, std::cout, std::endl;
using std::vector;

template<class T>
using array_10 = std::array<T, 10>;


int main() {

    vector arr = {2,3,4,6,1,5,7,0,9,8};

    cerr << arr << endl;

    //quick_sort(arr);
    //quick_sort1(arr);
    quick_sort2(arr);
    //quick_sort3(arr);

    cerr << arr << endl;

}

