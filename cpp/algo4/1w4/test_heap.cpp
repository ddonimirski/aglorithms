#include <iostream>
#include <vector>
#include "heap.hpp"
#include "../cmp.hpp"
#include "../pr.hpp"

using std::array;
using std::cout;

int main()
{
    //std::vector arr = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    std::vector arr = {12,13,14,0,7,11,3,10,2,4,6,5,8,9,1};
    pr("is_heap", to_str(is_heap(arr)));
    make_heap(arr);
    pr("is_heap", to_str(is_heap(arr)));
    pr(arr);
    pr("top:", ::top(arr, arr.size()));
    pr("is_heap", to_str(is_heap(arr, arr.size()-1)));
    pr(arr);
    pr("top:", ::top(arr, arr.size()-1));
    pr("is_heap", to_str(is_heap(arr, arr.size()-2)));
    pr(arr);
    make_heap(arr);
    pr(to_str(is_heap(arr)));
    heap_sort(arr);
    pr("sorted", arr);
}
