#if !defined SORT_HPP
#define SORT_HPP
#include <array>


template<class CONT>
void swap(CONT& arr, size_t i, size_t j)
{
    auto tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}


struct less_c
{
    template<class T>
    static bool cmp(T const& v1, T const& v2) 
    {
        return v1 < v2;
    }
};


template<class CONT, class CMP=less_c>
void sort_selection(CONT& arr)
{
    auto const N = arr.size();

    for (size_t i = 0; i < N-1; ++i)
    {
        int min = i;
        for (size_t j = i+1; j < N; ++j)
        {
            if (CMP::cmp(arr[min], arr[j]))
            {
                min = j;
            }
        }
        swap(arr, i, min);
    }
}


template<class CONT, class CMP=less_c>
void sort_insertion(CONT& arr)
{
    auto const N = arr.size();
    for (size_t i = 1; i < N; ++i)
    {
        for (size_t j = i; j > 0; --j)
        {
            auto const k = j - 1;

            if (CMP::cmp(arr[k], arr[j]))
            {
                swap(arr, k, j);
                continue;
            }
            break;
        }
    }
}


template<class CONT, class CMP=less_c>
void sort_shell(CONT& arr)
{
    auto const N = arr.size();

    size_t h = 1;

    while (h < N/3) h = 3 * h + 1;

    while (h >= 1)
    {
        for (size_t i = h; i < N; ++i)
        {
            for (int j = i; j > h-1; j -= h)
            {
                auto const k = j - h;
                if (CMP::cmp(arr[k], arr[j]))
                {
                    swap(arr, k, j);
                    continue;
                }
                break;
            }
        }

        h /= 3;
    }
}

#endif //SORT_HPP
