#if !defined SWAP_HPP
#define SWAP_HPP

template<class CONT>
void swap(CONT& arr, size_t i, size_t j)
{
    auto tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

template<class T>
void swap(T& v1, T& v2)
{
    T tmp{v1};
    v1 = v2;
    v2 = std::move(tmp);
}


#endif //SWAP_HPP
