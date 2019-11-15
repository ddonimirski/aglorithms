#include "sort.hpp"
#include <cassert>
#include <iostream>

template<class CONT, class CMP=less_c>
bool check(CONT const& cont)
{
    for (int i = 1; i < cont.size(); ++i)
    {
        if (CMP::cmp(cont[i-1], cont[i]))
        {
            return false;
        }
    }
    return true;
}

int main()
{
    {
        std::array<int, 10> arr = { 2, 4, 5, 2, 5, 6, 0, 7, 1, 9};
        sort_selection(arr);
        assert(check(arr));
    }
    {
        std::array<int, 10> arr = { 2, 4, 5, 2, 5, 6, 0, 7, 1, 9};
        sort_insertion(arr);
        assert(check(arr));
    }
    {
        std::array<int, 10> arr = { 2, 4, 5, 2, 5, 6, 0, 7, 1, 9};
        sort_shell(arr);
        assert(check(arr));
    }
}
