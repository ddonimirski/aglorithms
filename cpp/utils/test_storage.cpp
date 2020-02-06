#include "storage.hpp"
#include <cassert>

#include <variant>
#include <list>

using std::cout, std::endl;

struct C {
    int a;
    int b;

    friend std::ostream& operator<< (std::ostream& os, C const& c) {
        return os << '(' << c.a << ',' << c.b <<')';
    }
};


template <class T>
using array_20 = std::array<T,20>;


int main() {

    //storage_type<C, array_20> s;
    storage_type<C, std::vector> s;
    cout << s << endl;

    while (!s.is_empty()) {
        auto const id = s.alloc();
        if (!id.is_NIL())
            s[id] = {-10,-20};
    }

    for (int i = 0; i < 10; i++) {
        auto const id = s.alloc();
        if (!id.is_NIL())
            s[id] = {-20,-20};
    }

    for (int i = 0; i < s.arr.size(); i++)
    {
        cout << s[i] << endl;
    }

    cout << s << endl;

    for (int i = 0; i < 20; ++i) {
        s.free(i);
    }

    cout << s << endl;
}
