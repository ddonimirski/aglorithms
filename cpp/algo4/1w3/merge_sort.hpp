#if !defined MERGE_SORT_HPP
#define MERGE_SORT_HPP
#include "cmp.hpp"
#include <array>
#include <algorithm>


template<class CONT, class CONT2, class CMP=::less>
void merge(CONT& arr, CONT2& aux, size_t l, size_t m, size_t h)
{
    size_t i = l, j = m+1;
    for (size_t k = l; k <= h; ++k)
    {
        if (i > m)                              arr[k] = aux[j++];
        else if (j > h)                         arr[k] = aux[i++];
        else if (CMP::compare(aux[j], aux[i]))  arr[k] = aux[j++];
        else                                    arr[k] = aux[i++];
    }
}


template<class CONT, class CONT2, class CMP=::less>
void sort_merge(CONT& arr, CONT2& aux, size_t l, size_t h)
{
    if (l == h) return;
    size_t m = (l + h) /2;
    sort_merge(aux, arr, l, m);
    sort_merge(aux, arr, m+1, h);
    if (!CMP::compare(aux[m+1], aux[m])) return;
    ::merge(arr, aux, l, m, h);
}


template<class CONT>
void sort_merge(CONT& arr)
{
    if (arr.size() == 0) return;
    auto const N = arr.size() - 1;
    auto aux = arr;
    sort_merge(arr, aux, 0, N);
}


template<class T, int N>
void sort_merge(T (&arr)[N])
{
    constexpr auto size = arr.size();
    if (arr.size() == 0) return;
    T aux[N];
    std::copy(arr, arr+N, aux);
    sort_merge(arr, aux, 0, N);
}


#endif //MERGE_SORT_HPP
