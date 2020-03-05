#include <cassert>
#include <array>
#include <vector>
#include "pr.hpp"

#include "2.5.hpp"

using std::vector;
using print::pr;


int main() {

    vector arr = {2,3,4,6,1,5,7,0,9,8};
    pr(arr);
    count_sort(arr);
    pr(arr);
}

