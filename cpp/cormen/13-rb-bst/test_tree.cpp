#include <iostream>
#include <array>
#include <cassert>
#include "red_black_bst.hpp"
#include "rb_bst.hpp"

using std::cout, std::cerr, std::endl;

template<class T>
using cont_type = std::array<T, 20>;

void test_rb_bst() {


    rb_bst<unsigned, int, cont_type> rb;

    auto test_insert_nodes = [&rb]() {
        //rb.insert(5, 60);
        //rb.insert(6, 50);
        //rb.insert(3, 40);
        //rb.insert(4, 30);
        //rb.insert(1, 20);
        //rb.insert(2, 10);

        //cerr << rb << endl;

        //rb.erase(3);


        rb.insert(1, 60);
        rb.insert(2, 50);
        rb.insert(3, 40);
        rb.insert(4, 30);
        rb.insert(5, 20);
        rb.insert(6, 10);
        rb.insert(7, 70);
        rb.insert(8, 80);
        rb.insert(9, 90);
        rb.insert(10, 90);
        rb.insert(11, 90);
        rb.insert(12, 90);
        rb.insert(13, 90);
        rb.insert(14, 90);
        rb.insert(15, 90);
        rb.insert(16, 90);
        rb.insert(17, 90);
        rb.insert(18, 90);

        cerr << rb << endl;
        rb.erase(8);
    };
    test_insert_nodes();

    cout << rb << endl;

    {
        auto [key, value] = rb.min();
        cout << key << ' ' << value << endl;
    }

    auto [key, value] = rb.max();
    cout << key << ' ' << value << endl;

    cout << *rb.get_value(key) << endl;
    cout << rb[rb.find_key(key)] << endl;
}

void test_red_black_bst() {
    red_black_bst<int, int> rb;

    //auto test_add_first_node = [&rb]() {
    //    rb.add(1, 10);
    //    rb.add(2, 20);
    //    rb.add(3, 30);
    //    rb.add(4, 40);
    //    rb.add(5, 50);
    //    rb.add(6, 60);
    //    rb.add(7, 70);
    //    rb.add(8, 80);
    //    rb.add(9, 90);
    //    rb.add(10, 100);
    //    rb.add(11, 110);
    //    rb.add(12, 120);
    //    rb.add(13, 130);
    //    rb.add(14, 140);
    //    rb.add(15, 150);
    //    rb.add(16, 160);
    //};
    //test_add_first_node();
}

int main() {
    // test_red_black_bst();
    test_rb_bst();
}
