#include <iostream>
#include <cassert>
#include "2.3.hpp"
#include <array>
#include <vector>
#include "pr.hpp"

using std::vector;
using print::pr;

int main() {

    {
        vector arr = {2,3,4,6,1,5,7,0,9,8};
        //pr(arr);

        //quick_sort(arr);
        //quick_sort1(arr);
        //quick_sort2(arr);
        //quick_sort3(arr);

        //pr(arr);
    }
    pr("-----\n");
    { /// only int greater then 0 :P but not unsigned int :P
        //vector arr = {7,3,4,6,1,5,2,10,9,8};
        vector arr = {7,6,5,3,1,4,2};
        pr(arr);
        quick_sort4(arr);
        pr(arr);
    }
}
