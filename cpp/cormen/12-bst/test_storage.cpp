#include "storage.hpp"
#include <cassert>

#include <variant>

using std::cout, std::endl;

struct C {
    int a;
    int b;

    friend std::ostream& operator<< (std::ostream& os, C const& c) {
        return os << '(' << c.a << ',' << c.b <<')';
    }
};

int main() {

    storage_type<C, std::array> s;
//    cout << s << endl;
//
//    while (!s.is_empty())
//        s[s.alloc()] = {-10,-20};
//
//
//    cout << s << endl;
//
//    for (int i = 0; i < 20; ++i) {
//        s.free(i);
//    }
//
//    cout << s << endl;
}
