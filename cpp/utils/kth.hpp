#if !defined KTH_HPP
#define KTH_HPP
#include <iterator>
#include <type_traits>

template <class T>
T kth_rec(size_t k, T const* b1, T const* e1, T const* b2, T const* e2) noexcept {
    if (b1 >= e1) return b2[k];
    if (b2 >= e2) return b1[k];

    auto const m1 = (e1 - b1) / 2;
    auto const m2 = (e2 - b2) / 2;

    if (k > m1+m2) {
        if (b1[m1] > b2[m2])
            return kth_rec(k-m2-1, b1, e1, b2+m2+1, e2);
        else
            return kth_rec(k-m1-1, b1+m1+1, e1, b2, e2);
    }
    else {
        if (b1[m1] > b2[m2])
            return kth_rec(k, b1, b1+m1, b2, e2);
        else
            return kth_rec(k, b1, e1, b2, b2+m2);
    }
}


template <class T>
T kth_iter(size_t k, T const* b1, T const* e1, T const* b2, T const* e2) noexcept {

    while(true) {
        if (b1 >= e1) return b2[k];
        if (b2 >= e2) return b1[k];

        auto const m1 = (e1 - b1) / 2;
        auto const m2 = (e2 - b2) / 2;

        if (k > m1+m2) {
            if (b1[m1] > b2[m2]) {
                k = k-m2-1;
                b2 = b2+m2+1;
            }
            else {
                k = k-m1-1;
                b1 = b1+m1+1;
            }
        }
        else {
            if (b1[m1] > b2[m2])
                e1 = b1+m1;
            else
                e2 = b2+m2;
        }
    }
}


template <class IA, class IB> // IA/IB - random access iterator
auto kth_iter_random_access(size_t k, IA b1, IA e1, IB b2, IB e2) noexcept {

    while(true) {
        if (b1 >= e1) return b2[k];
        if (b2 >= e2) return b1[k];

        auto const m1 = std::distance(b1, e1) / 2;
        auto const m2 = std::distance(b2, e2) / 2;

        if (k > m1+m2) {
            if (b1[m1] > b2[m2]) {
                k = k-m2-1;
                b2 = b2+m2+1;
            }
            else {
                k = k-m1-1;
                b1 = b1+m1+1;
            }
        }
        else {
            if (b1[m1] > b2[m2])
                e1 = b1+m1;
            else
                e2 = b2+m2;
        }
    }
}


template <class IA, class IB> // IA/IB - random access iterator
auto kth_iter_forward(size_t k, IA b1, IA e1, IB b2, IB e2) noexcept {
    static_assert(std::is_same<IA, IB>::value);
    auto ret = { *b1, *b2 };
    return ret;
}

template <class IA, class IB> // IA/IB - random access iterator
auto kth_iter(size_t k, IA b1, IA e1, IB b2, IB e2) noexcept {
    using category_A = typename std::iterator_traits<IA>::iterator_category;
    using category_B = typename std::iterator_traits<IB>::iterator_category;
    if constexpr (std::is_same<category_A, std::random_access_iterator_tag>::value
               && std::is_same<category_B, std::random_access_iterator_tag>::value) {
        //return kth_iter_random_access(k, b1, e1, b2, e1);
    }
    else {
        return kth_iter_forward(k, b1, e1, b2, e2);
    }

}


#endif // KTH_HPP
