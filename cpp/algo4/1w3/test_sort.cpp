#include "cmp.hpp"
#include "pr.hpp"
#include "test.hpp"
#include "merge_sort.hpp"
#include "quick_sort.hpp"
#include <iostream>


int main()
{
    {
        std::array<int, 10> arr = { 3, 2, 4, 5, 6, 0, 7, 1, 9, 8};
        sort_merge(arr);
        assert(is_sorted(arr));
        pr(arr);
    }
    {
        int arr[] = { 3, 2, 4, 5, 6, 0, 7, 1, 9, 8};
        quick_sort(arr);
        assert(is_sorted(arr));
        pr(carr(arr));
    }
    {
        std::array<int, 10> arr = { 3, 2, 4, 4, 3, 0, 7, 1, 9, 3};
        quick_sort3w(arr);
        pr(arr);
    }
}
