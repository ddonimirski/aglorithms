#include "cmp.hpp"
#include "merge_sort.hpp"
#include "test.hpp"
#include <cassert>
#include <iostream>


int main()
{
    {
        std::array<int, 10> arr = { 2, 4, 5, 2, 5, 6, 0, 7, 1, 9};
        sort_merge(arr);
        assert(is_sorted(arr));
    }

}
