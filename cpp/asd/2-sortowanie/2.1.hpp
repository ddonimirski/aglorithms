#if !defined SELECTION_SORT_HPP
#define SELECTION_SORT_HPP

template<class T, template<typename...> class C>
void selection_sort(C<T>& arr) noexcept {
    auto swap = [&arr](auto i, auto j) noexcept {
        auto const tmp = std::move(arr[i]);
        arr[i] = std::move(arr[j]);
        arr[j] = std::move(tmp);
    };

    //TODO: pass condition as paramiter
    auto less = [&arr] (auto i, auto j) noexcept -> bool {
        return arr[i] < arr[j];
    };

    auto find_ext = [&arr, &less, size=arr.size()](auto b) noexcept {
       for (auto i = b+1; i < size; ++i) {
           if (less(i, b)) b = i;
       }
       return b;
    };

    auto const size = arr.size();
    if (size < 2) return;
    for (auto e = 0u; e < size-1; ++e) {
        if (auto const m = find_ext(e); m != e) {
            swap(m, e);
        }
    }
}

#endif // SELECTION_SORT_HPP
