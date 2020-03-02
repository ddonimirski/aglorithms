#if !defined INSERTION_SORT_HPP
#define INSERTION_SORT_HPP

template<class T, template<typename...> class C>
void insertion_sort(C<T>& arr) noexcept {
    auto swap = [&arr](auto i, auto j) noexcept {
        auto const tmp = std::move(arr[i]);
        arr[i] = std::move(arr[j]);
        arr[j] = std::move(tmp);
    };

    //TODO: pass condition as paramiter
    auto less = [&arr] (auto i, auto j) noexcept -> bool {
        return arr[i] < arr[j];
    };

    auto const size = arr.size();
    for (auto i = 1u; i < size; ++i) {
        for (auto j = i; j > 0 && less(j, j-1); --j) { //swap all pairs until
            swap(j-1, j);
        }
    }
}

#endif //INSERTION_SORT_HPP
