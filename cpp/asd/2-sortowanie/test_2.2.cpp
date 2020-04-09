#include <cassert>
#include <array>
#include <vector>
#include "pr.hpp"
#include "2.2.hpp"

using std::vector;
using print::pr;

template<class T>
using array_10 = std::array<T, 10>;

int main() {

    vector arr = {2,3,4,6,1,5,7,0,9,8};

    pr(arr);

    insertion_sort(arr);

    pr(arr);
}
