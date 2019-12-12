#if !defined QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include "swap.hpp"
struct range
{
    size_t l;
    size_t r;
};

template<class CONT, class CMP=::less>
range partition_equal(CONT& arr, size_t l, size_t h)
{
    range r = {l, h};
    size_t i = l+1;
    while (i <= r.r)
    {
        while (CMP::compare(arr[i], arr[r.l]))
        {
            ::swap(arr, r.l++, i++);
            if (i == r.r) break;
        }

        while (arr[r.l] == arr[i])
        {
            if (++i == r.r) break;
        }

        while (CMP::compare(arr[r.l], arr[r.r]))
        {
            if (--r.r == i) break;
        }

        if (i > r.r) break;
        ::swap(arr[i], arr[r.r]);
    }
    return r;
}

template<class CONT, class CMP=::less>
size_t partition(CONT& arr, size_t l, size_t h)
{
    auto i = l + 1, j = h;
    while (true)
    {
        while (CMP::compare(arr[l], arr[j]))
            if (l == --j) break;

        while (CMP::compare(arr[i], arr[l]))
            if (h == ++i) break;

        if (i >= j) break;

        ::swap(arr, i, j);
    }
    ::swap(arr, l ,j);
    return j;
}

template<class CONT, class CMP=::less>
void quick_sort3w(CONT& arr, size_t l, size_t h)
{
    if (l >= h) return;
    auto const[lr, rr] = partition_equal<CONT, CMP>(arr, l, h);
    quick_sort3w(arr, l, lr==0?0:lr-1);
    quick_sort3w(arr, rr+1, h);
}

template<class CONT, class CMP=::less>
void quick_sort(CONT& arr, size_t l, size_t h)
{
    if (l >= h) return;
    auto const m = partition<CONT, CMP>(arr, l, h);
    quick_sort(arr, l, m==0?0:m-1);
    quick_sort(arr, m+1, h);
}


template<class CONT, class CMP=::less>
void quick_sort3w(CONT& arr)
{
   //shuffle 
   quick_sort3w<CONT, CMP>(arr, 0, arr.size()-1);
}

template<class CONT, class CMP=::less>
void quick_sort(CONT& arr)
{
    //shuttle
    quick_sort<CONT, CMP>(arr, 0, arr.size()-1);
}

template<class T, int N, class CMP=::less>
void quick_sort(T (&arr)[N])
{
    //shuttle
    quick_sort(arr, 0, N-1);
}

template<class T, class CMP=::less>
void quick_sort(T const* arr, size_t N)
{
    if (N == 0) return;
    //shuttle
    quick_sort(arr, 0, N-1);
}

template<class T, int N, class CMP=::less>
size_t select(T (&arr)[N], T const& key)
{
}

#endif //QUICK_SORT_HPP
