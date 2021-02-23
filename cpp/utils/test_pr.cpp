#include "pr.hpp"
#include <ostream>
#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <string>
#include "gtest/gtest.h"

using std::cout;

#if 0
int main()
{
    //std::array arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    //cout << arr << '\n';

    std::vector vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    cout << vec << '\n';

    int c_arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    cout << c_arr << '\n';

    std::list ll = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    cout << ll << '\n';
    std::string const s = "noga \n";

    pr(sep{'\n'}, "c array", carr(c_arr), /*"std::array", arr,*/ "std::vector", vec, "std::list", ll);

}
#endif

TEST(pr, test) {
}


