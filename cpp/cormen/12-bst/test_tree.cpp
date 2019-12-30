#include "tree.hpp"
#include "red_black_bst.hpp"
#include <iostream>

using std::cout, std::endl;

int main() {

    //tree_us<int, 16> tt;
    //tt.add(8);
    //tt.add(4);
    //tt.add(2);
    //tt.add(6);
    //tt.add(1);
    //tt.add(3);
    //tt.add(5);
    //tt.add(7);
    //cout << tt << endl;
    //tt.print();
    

    red_black_bst<int> rb;

    cout << rb << endl;

    cout << std::hex << (rb.storage[19].parent_id()) << endl;
    cout << std::hex << (rb.storage[19].is_red()) << endl;

}
