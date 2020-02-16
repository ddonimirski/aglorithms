#if !defined MEDIAN_HPP 
#define MEDIAN_HPP 

#include "kth.hpp"

template <class T, size_t N, size_t M>
double median(T (&a)[N], T (&b)[M]) {
    auto const size = N + M;
    if (!size) return 0.0;
    auto const k = size / 2; // kth index
    double ret = kth_iter(k, a, a+N, b, b+M);
    if (size%2) return ret;
    return (ret + kth_iter(k-1, a, a+N, b, b+M))/2;
}


template <class T>
double median(T const* a, size_t al,  T const* b, size_t bl) {
    auto const size = al + bl;
    if (!size) return 0.0;
    auto const k = size / 2; // kth index
    double ret = kth_iter(k, a, a+al, b, b+bl);
    if (size%2) return ret;
    return (ret + kth_iter(k-1, a, a+al, b, b+bl))/2;
}


template <class T1, class T2, template<typename...> class CONT>
double median(CONT<T1>& a, CONT<T2>& b) {
    auto const size = a.size() + b.size();
    if (!size) return 0.0;
    auto const k = size / 2; // kth index
    double const ret = kth_iter(k, a.begin(), a.end(), b.begin(), b.end());
    if (size%2) return ret;
    return (ret + kth_iter(k-1, a.begin(), a.end(), b.begin(), b.end()))/2;
}


#endif // MEDIAN_HPP 
