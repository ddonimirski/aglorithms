#include "tree.hpp"
#include "red_black_bst.hpp"
#include <iostream>
#include <cassert>

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
    red_black_bst<int> rb;

    auto test_free_space = [&rb]() {
    };
    test_free_space();

    auto test_add_first_node = [&rb]() {
        rb.add(1, 10);
        rb.add(3, 30);
        rb.add(2, 20);
        rb.add(4, 40);
    };
    test_add_first_node();

    auto test_red_black = [&rb]() {
        rb[3].set_red();
    };
    test_red_black();

    auto test_rotate = [&rb]() {
        rb.rotate_left(1);
    };
    test_rotate();

    cout << rb << endl;

}

int main() {


    test_red_black_bst();
}
