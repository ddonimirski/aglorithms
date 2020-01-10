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
    red_black_bst<int, int> rb;

    //auto test_free_space = [&rb]() {
    //};
    //test_free_space();

    auto test_add_first_node = [&rb]() {
        rb.add(1, 10);
        rb.add(2, 20);
        rb.add(3, 30);
        rb.add(4, 40);
        rb.add(5, 50);
        rb.add(6, 60);
        rb.add(7, 70);
        rb.add(8, 80);
        rb.add(9, 90);
        rb.add(10, 100);
        rb.add(11, 110);
        rb.add(12, 120);
        rb.add(13, 130);
        rb.add(14, 140);
        rb.add(15, 150);
        rb.add(16, 160);
    };
    test_add_first_node();

    cout << rb << endl;
    //cout << rb.min() << endl;
    //cout << rb.max() << endl;
}

int main() {


    test_red_black_bst();
}
