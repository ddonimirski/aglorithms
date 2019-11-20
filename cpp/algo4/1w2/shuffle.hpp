#if !defined SHUFFLE_HPP
#define SHUFFLE_HPP
#include <random>

#include <iostream>
using namespace std;

template<class CONT>
void swap(CONT& arr, int i, int j)
{
    cout << i << ' ' << j << endl;
    auto tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

template<class CONT>
void suffle(CONT& arr)
{
    std::random_device rd;
    std::mt19937 gen(rd());


    for (int i = 0; i < arr.size(); ++i)
    {
        std::uniform_int_distribution<> dis(0, i);
        swap(arr, i, dis(gen));

    }
}


template<class CONT>
void suffle_part(CONT& arr, int size)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    if (size > arr.size()) size = arr.size();

    for (int i = 0; i < size; ++i)
    {
        std::uniform_int_distribution<> dis(0, i);

    }


    for (int i = 0; i < arr.size(); ++i)
    {
        std::uniform_int_distribution<> dis(0, i);
        swap(arr, i, dis(gen));

    }
}


#endif //SHUFFLE_HPP
