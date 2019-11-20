#include "pr.hpp"
#include <ostream>
#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <string>

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
    std::string const s = "noga \n";

    pr(sep_t{'\n'}, "c array", carr, "std::array", arr, "std::vector", vec, "std::list", ll);

}
