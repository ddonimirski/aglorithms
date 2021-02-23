#include <iostream>
#include <cassert>
#include <vector>

using std::cout, std::cerr , std::endl;
using std::cin;
using std::vector;


template<class T>
struct stack {
    vector<T> storage;
    int curr_top = -1;
};
