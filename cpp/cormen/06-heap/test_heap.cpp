#include "heap.hpp"
#include <iostream>
#include <cassert>

#include <array>
#include <vector>
#include <algorithm>
#include <random>

using std::cout, std::cerr, std::endl;
using std::copy;


template<class CONT, class CMP>
bool check_sort(CONT const& cont, CMP cmp) {
    for (size_t i = 1; i < cont.size(); ++i)
        if (!cmp(cont[i-1], cont[i]))
            return false;
    return true;
}

template<class T>
struct arr {
    std::array<T, 20> _a;
    size_t _s = 0u;

    size_t size() const { return _s; }

    T& operator[](size_t i) {
        return _a[i];
    }

    T const& operator[](size_t i) const {
        return _a[i];
    }

    auto begin() { return _a.begin(); }
    auto end() { return _a.begin() + _s; }

    void ext() { _s = _a.size(); }
};

template<class T, template<typename...> class CONT>
void pr(CONT<T>& arr) {
    for (auto const& v: arr)
        cerr << v << ' ';
    cerr << endl;
}


int main() {

    std::vector v = {2, 3, 4, 1};
    //auto& a = v;
    arr<int> a;
    //
    //copy(v.begin(), v.end(), a._a.begin());
    //a._s = v.size();
    //

    //a.ext();
    a._s = 10;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 30);
    auto fun = [&gen, &dist]() { return dist(gen); };

    auto c = 100000u;
    while (--c) {
        std::generate(a.begin(), a.end(), fun);
        heap h {a, a.size()};

        if (!is_heap(h)) cout << "NOT HEAP: " << h << endl;

        int i = 0;
        heap<int, std::vector> h2;
        while(h.size()) {
            auto const v = h.pop();
            a[i++] = v;
            h2.insert(v);
        }

        if (auto v = !check_sort(a, min_cmp<int>{}))
            cerr << "is sorted " << check_sort(a, min_cmp<int>{}) << endl;

    }
     
}
