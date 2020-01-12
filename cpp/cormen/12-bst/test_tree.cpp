#include <iostream>
#include <cassert>
#include "tree.hpp"
#include "red_black_bst.hpp"

using std::cout, std::endl;

void test_bst() {
    tree_us<int, 16> tt;
    tt.add(8);
    tt.add(4);
    tt.add(2);
    tt.add(6);
    tt.add(1);
    tt.add(3);
    tt.add(5);
    tt.add(7);
    cout << tt << endl;
    tt.print();
}

void test_red_black_bst() {
}

int main() {


}
