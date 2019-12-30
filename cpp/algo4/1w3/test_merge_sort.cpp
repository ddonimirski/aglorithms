#include "cmp.hpp"
#include "pr.hpp"
#include "test.hpp"
#include "merge_sort.hpp"
#include "quick_sort.hpp"
#include <iostream>


int main()
{
    {
        //std::array<int, 10> arr = { 3, 2, 4, 5, 6, 0, 7, 1, 9, 8};
        //sort_merge(arr);
        //pr(arr);
        //assert(is_sorted(arr));
        //
    }
    {
        std::array<int, 10> arr = { 3, 2, 4, 5, 6, 0, 7, 1, 9, 8};
        sort_quick(arr);
        pr(arr);
        //assert(is_sorted(arr));
    }

}
