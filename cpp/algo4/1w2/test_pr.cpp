#include "pr.hpp"
#include <ostream>
#include <iostream>
#include <array>
#include <vector>
#include <list>

using std::cout;

int main()
{
    std::array arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    cout << arr << '\n';

    std::vector vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    cout << vec << '\n';

    int carr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    cout << carr << '\n';

    std::list ll = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    cout << ll << '\n';

}
