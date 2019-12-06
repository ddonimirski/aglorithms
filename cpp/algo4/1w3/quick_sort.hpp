#if !defined QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include "swap.hpp"

template<class CONT, class CMP=::less>
void partition(CONT& arr, size_t l, size_t h)
{
    if (l+2 == h) return;
    auto i = l + 1, j = h;
    while (i != j)
    {
        if (CMP::compare(arr[j], arr[j])
    }
}

#endif //QUICK_SORT_HPP
