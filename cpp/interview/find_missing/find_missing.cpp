// find_missing the array consits conscutives number but one can be missing
// function should find this number and return it or if table has concecutives
// numbers should print 0
//
#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>
#include <array>

//add concept for Item
template <class Item>
auto find_missing(Item const* arr, ptrdiff_t n) -> Item {

    ptrdiff_t b = 0;
    ptrdiff_t e = n - 1;
    ptrdiff_t p = (e - b) / 2;

    while (b < p)
    {
        auto const s = arr[p] - arr[b];
        auto const d = p - b;

        if (s != d) {
            e = p;
            p = b + (p - b) / 2;
        }
        else {
            b = p;
            p = e;
        }
    }

    if (b >= 0 && b < n - 1 && arr[b]+1 != arr[b+1])
    {
        return arr[b] + 1;
    }

    if (b > 0 && b < n && arr[b]-1 != arr[b-1])
    {
        return arr[b] - 1;
    }

    return {}; // 0 :P
}

template<class Item, int N>
auto find_missing(Item (&arr)[N]) {
    return find_missing(arr, N);
}

template<class Item, class ...Args>
auto find_missing(std::vector<Item,Args...> const& vec) {
    return find_missing(vec.data(), vec.size());
}

template<class Item, std::size_t N>
auto find_missing(std::array<Item, N> const& arr) {
    return find_missing(arr.data(), arr.size());
}


int main() {

    std::array<int,5> vec = { 1, 2, 3, 4, 5};

    std::cerr << find_missing(vec);

}
