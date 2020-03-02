#if !defined QUICK_SORT_HPP
#define QUICK_SORT_HPP
#include <stack>

#include <iostream>
using std::cerr, std::endl;

template<class T, template<typename...> class C>
auto partition(C<T>& arr, size_t b, size_t e) noexcept {
    auto swap = [&arr](auto i , auto j) noexcept {
        auto const t = std::move(arr[i]);
        arr[i] = std::move(arr[j]);
        arr[j] = std::move(t);
    };
    auto less = [&arr](auto i, auto j) noexcept {
        return arr[i] < arr[j];
    };
    auto l = b+1;
    for (auto r = b+1; r <= e; ++r) {
        if (less(r, b)) {
            if (r != l) swap(r, l);
            l++;
        }
    }
    swap(l-1, b);
    return l-1;
}

static int a = 0;

template<class T, template<typename...> class C>
void quick_sort_impl_rec(C<T>& arr, size_t b, size_t e) {
    auto const p = partition(arr, b, e);
    if (b < p) quick_sort_impl_rec(arr, b, p-1);
    if (p < e) quick_sort_impl_rec(arr, p+1, e);
}

template<class T, template<typename...> class C>
void quick_sort(C<T>& arr) {
    if (arr.size() < 2) return;
    quick_sort_impl_rec(arr, 0u, arr.size()-1u);
}


template<class T, template<typename...> class C>
void quick_sort1(C<T>& arr) {

    struct pp { size_t l, r; };
    std::stack<pp> s;

    auto const n = arr.size()-1;

    if (n > 1) {
        s.push({0, n});
        do {
            auto [l, r] = s.top(); s.pop();
            while (l < r+1) {
                auto const j = partition(arr, l, r);
                if (j-l < r-j) {
                    s.push({j+1, r});
                    r = j - 1;
                }
                else {
                    s.push({l, j-1});
                    l = j+1;
                }
            }
        } while (s.size() != 0);
    }
}


template<class T, template<typename...> class C>
void quick_sort2(C<T>& arr) {

    struct pp { size_t l, r; };
    std::stack<pp> s;

    auto const n = arr.size();

    if (n > 1) {
        s.push({0, n});
        do {
            auto [l, r] = s.top(); s.pop();
            while (r - l > 1) { // m == 1
                auto const j = partition(arr, l, r);
                if (j >= r) break;
                s.push({j+1, r});
                r = j-1;
            }
            // wykonaj insertion_sort (r - l <= m)
        } while(s.size() != 0);
    }
}


template<class T, template<typename...> class C>
void quick_sort3(C<T>& arr) {

    std::stack<int> s;
    auto const n = arr.size();

    if (n > 2) {
        s.push(n);
        auto r = -1;
        do {
            auto l = r + 2;
            auto r = s.top(); s.pop();
            while (r - l > 1) { // m == 1
                auto const j = partition(arr, l, r);
                if (j >= r) break;
                s.push(r);
                r = j - 1;
            }
            // insertion_sort for r - l < m
        } while(s.size() != 0);
    }
}

#endif //QUICK_SORT_HPP
