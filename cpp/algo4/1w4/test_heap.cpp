#include <iostream>
#include <array>
#include "heap.hpp"
#include "../cmp.hpp"
#include "../pr.hpp"

using std::array;
using std::cout;

int main()
{
    array<int,15> arr = {12,13,14,0,7,11,3,10,2,4,6,5,8,9,1};
    pr(is_heap(arr));
    make_heap(arr);
    pr(is_heap(arr));
    pr_cont(cout, arr);
    pr(::top(arr, arr.size()));
    pr("is_heap", is_heap(arr));
    cout << '\n';
    pr_cont(cout, arr);
    pr(::top(arr, arr.size()-1));
    pr("is_heap", is_heap(arr));
    cout << '\n';
    pr_cont(cout, arr);
    heap_sort(arr);
    pr_cont(cout, arr);
}
