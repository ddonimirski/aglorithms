//#include "pr.hpp"
#include <ostream>
#include <iostream>
#include <array>
#include <vector>

template<class CONT>
std::ostream& operator << (std::ostream& os, const CONT& arr)
{
    //os << '[' << ' ';
    //for (auto const v: arr)
    //    os << v << ' ';
    //for (auto const& v: arr)
    //    std::cout << v << ' ';
    return os;
}


int main()
{
    std::array arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int carr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    std::cout << carr;

    for (int i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i] << ' ' ;
    }
}
