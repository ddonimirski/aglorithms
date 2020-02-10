#include <iostream>
#include <algorithm>
#include <cassert>

template<class T>
void swap(T* a, T* b)
{
    auto const t = *a;
    *a = *b;
    *b = t;
}

template<class T>
int partition(T a[], int l, int r)
{

    auto p = a[r];
    int i = l - 1;

    for (int j = 1; j <= r-1; ++j)
    {
        if (a[j] <= p)
        {
            swap(&a[++i], &a[j]);
        }
    }

    swap(&a[i+1], &a[r]);

    return i + 1;
}

template<class RandIter>
RandIter partition(RandIter l, RandIter r)
{
    for (RandIter j = l; j < r; ++j)
    {
        if (*j <= *r)
        {
            std::iter_swap(l++, j);
        }
    }
    std::iter_swap(l, r);
    retur l;
}


int main()
{
    {
        int a[] =    {8, 1, 6, 4, 0, 3, 9, 5};
        int aref[] = {1, 4, 0, 3, 5, 8, 9, 6};

        auto p = partition(a, 0, 7);

        assert(std::equal(std::begin(a),
                    std::end(a),
                    std::begin(aref)));

        assert(p == 4);
        assert(a[p] == 5);
    }

    {
        int a[] =    {8, 1, 6, 4, 0, 3, 9, 5};
        auto* p = partition(a, a+7);
        std::cout << "Array ater partition" << std::endl;

        for (auto e: a)
            std::cout << e << ' ' ;
        std::cout << std::endl;

        std::cout << "partition index: "
            << std::distance(std::begin(a), p) << ", "
            << "partition element: " << *p
            << std::endl;
    }
}
