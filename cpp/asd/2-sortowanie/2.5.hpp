#if !defined COUNT_SORT_HPP
#define COUNT_SORT_HPP

#include "pr.hpp"
using print::pr;


template<class T, template<typename...> class C, size_t MIN=0, size_t MAX=100>
void count_sort(C<T>& arr) {
    //TODO: check_min_max
    //is_integral
    size_t count[MAX-MIN+1];
    for (auto v: arr) ++count[v-MIN];
}

#endif //COUNT_SORT_HPP
