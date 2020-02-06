#include <iostream>
#include <vector>
#include <cassert>

using std::cout, std::cerr, std::endl;


template<class T, template <typename...> class C, class I>
T sum(C<T> const& c, I i)  {
    if (i == c.size()) return T{};
    return c[i] + sum(c, i+1);
}


int main() {

    std::vector v = { 1, 2, 3, 4, 5, 6 };

    cout << sum(v, 0) << endl;
}


