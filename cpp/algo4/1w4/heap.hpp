#if !defined HEAP_HPP
#define HEAP_HPP

#include "../cmp.hpp"
#include "../swap.hpp"


template<class CONT, class CMP=::less>
bool is_heap(CONT& arr, size_t N)
{
    N /= 2;
    for (size_t p = 0; p < N; ++p)
    {
        auto const l = 2*p+1;
        if (l < N && !CMP::compare(arr[p], arr[l]))
            return false;
        auto const r = 2*(p+1);
        if (r < N && !CMP::compare(arr[p], arr[r]))
            return false;

    }
    return true;
}

template<class T, size_t N, class CMP=::less>
bool is_heap(T const (&arr)[N])
{
    return is_heap(arr, N);
}


template<class T, template<typename> class CONT, class CMP=::less>
bool is_heap(CONT<T>& arr)
{
    return is_heap(arr, arr.size());
}

template<class CONT, class CMP=::less>
void swim(CONT& arr, size_t k, size_t N)
{
    for (auto p = k/2; k > 0 && CMP::compare(arr[k], arr[p]); k=p, p=k/2) 
    {
        ::swap(arr, k, p);
    }
}


template<class CONT, class CMP=::less>
void sink(CONT& arr, size_t k, size_t N)
{
    while (k < N/2)
    {
        auto i = 2*k+1;
        if (i < N && CMP::compare(arr[i+1], arr[i])) ++i;
        if (!CMP::compare(arr[i], arr[k])) break;
        ::swap(arr, k, i);
        k = i;
    }
}


template<class CONT, class CMP=::less>
void make_heap(CONT& arr)
{
    for (size_t i = 0; i < arr.size(); i++)
        swim<CONT,CMP>(arr, i, arr.size());
}

template<class CONT, class CMP=::less>
auto top(CONT& arr, size_t N)
{
    auto const ret = arr[0];
    ::swap(arr[0], arr[--N]);
    sink<CONT,CMP>(arr, 0, N);
    return ret;
}

template<class CONT, class CMP=::less>
void heap_sort(CONT& arr)
{
    if (arr.size() == 0) return;
    make_heap<CONT,CMP>(arr);

    auto N = arr.size()-1;
    while (N)
    {
        ::swap(arr, 0, N--);
        sink<CONT,CMP>(arr, 0, N);
    }
}

#endif //HEAP_HPP

