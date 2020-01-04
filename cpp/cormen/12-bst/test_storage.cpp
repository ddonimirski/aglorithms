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


    id_type id;

    assert (is_NIL(id));
    assert (!is_on(id));
    on(id);
    assert (is_NIL(id));
    assert (is_on(id));
    off(id);
    assert (is_NIL(id));
    assert (!is_on(id));
    flip(id);
    assert (is_NIL(id));
    assert (is_on(id));
    flip(id);
    assert (is_NIL(id));
    assert (!is_on(id));

    id = 1u;
    assert (id == 1u);
    assert (!is_on(id));
    flip(id);
    assert (id == 1u);
    assert (is_on(id));
    id = 2;
    assert (id == 2u);
    assert (is_on(id));
    flip(id);
    assert (id == 2u);
    assert (!is_on(id));

    id = id_type::NIL;
    assert (is_NIL(id));
    assert (!is_on(id));
    id = 3;
    assert (id == 3u);
    assert (!is_on(id));
    flip(id);
    assert (id == 3u);
    assert (is_on(id));

    id = id_type();
    assert (is_NIL(id));
    assert (is_on(id));

    cout << is_on(id) << ' ' << id << endl;

}
