#include <cassert>
#include <array>
#include <vector>
#include "2.1.hpp"
#include "pr.hpp"

using print::pr;
using std::vector;

template<class T>
using array_10 = std::array<T, 10>;

int main() {

    vector arr = {2,3,4,6,1,5,7,0,9,8};

    pr(arr);

    selection_sort(arr);

    pr(arr);
}

