#include <iostream>
#include <cassert>
#include <string>

using std::cout, std::cerr, std::endl;
using std::string;

void revers(char* str, size_t len) {
    bool p = len%2;
    auto l = 0u;
    auto r = l-1;

    while (l<r) {
        auto const t = str[l];
        str[l] = str[r];
        str[r] = t;
        --r;
        --l;
    }
}


int main() {
    char str[] = "nowa";

    cout << str << endl;
    revers(str, 4);
    cout << str << endl;
}
