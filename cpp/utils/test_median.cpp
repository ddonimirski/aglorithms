#include <iostream>
#include <vector>
#include <list>
#include <forward_list>

#include "median.hpp"

using std::cout, std::endl;
using std::vector;
using std::list;
using std::forward_list;


int main() {

    int a[] = {1, 2, 4, 5, 8};
    int b[] = {3, 6, 7};
    auto const al = sizeof(a)/sizeof(*a);
    auto const bl = sizeof(b)/sizeof(*b);

    cout << median(a, b) << endl;
    cout << median(a, al, b, bl) << endl;

    vector va = {1, 2, 4, 5, 8};
    vector vb = {3, 6, 7};
    cout << median(va, vb) << endl;

    list la = {1, 2, 4, 5, 8};
    list lb = {3, 6, 7};
    auto [am, bm] = median(la, lb);

    // forward_list la = {1, 2, 4, 5, 8};
    // forward_list lb = {3, 6, 7};
    // auto [am, bm] = median(la, lb);
    //cout << am << ' ' << bm  << endl;
}
