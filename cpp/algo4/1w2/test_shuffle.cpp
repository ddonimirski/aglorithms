#include "shuffle.hpp"
#include <array>

#include <iostream>
using namespace std;

template<class CONT>
void pr(CONT const& arr)
{
    for (auto const v: arr)
    {
        cout << v << ' ';
    }
    cout << '\n';
}


int main()
{
    {
        std::array<int, 10> arr = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        suffle(arr);
        pr(arr);
    }
}
