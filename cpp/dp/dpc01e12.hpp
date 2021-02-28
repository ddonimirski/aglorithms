#if !defined DP_CH01_E12
#define DP_CH01_E12

namespace dp::ch01::e12
{
// bubble_sort
//
//

template<class T>
void swap_int(T& v1, T& v2) {
    v1 ^= v2;
    v2 ^= v1;
    v1 ^= v2;
}

template<class T, template<typename...> class C>
void bubble_sort(C<T>& c) {
    for (int i = 0; i < c.size(); ++i) {
        for (int j = 0; j < c.size()-1; ++j) {
            if (c[j] < c[j+1])
                swap_int(c[j], c[j+1]);
        }
    }
}


template<class T, template<typename...> class C>
void bubble_sort_rec(C<T>& c, size_t n) {
    if (n == 0) return;
    for (size_t j = 0; j < n-1; ++j) {
        if (c[j] < c[j+1])
            swap_int(c[j], c[j+1]);
    }
    bubble_sort_rec(c, n-1);
}

template<class T, template<typename...> class C>
void bubble_sort_rec(C<T>& c) {
    bubble_sort_rec(c, c.size());
}

} // namespace dp::c01::e12

#endif // DP_CH01_E12
