#include <iostream>
#include "id_type.hpp"
#include "gtest/gtest.h"



TEST(id_type, test) {

    id_ui0f_type id0;
    id_ui1f_type id1;
    id_ui2f_type id2;

    id1.on();
    id2.on();

    // cout << (sizeof(unsigned) * 8)-1 << endl;

    // cout << id0 << endl;
    // cout << id1 << endl;
    // cout << id2 << endl;

    id1.off();
    id2.off();

    id2.set_flag(1);
    id2.set_flag(0);
    

    // cout << id0 << endl;
    // cout << id1 << ' ' << id1.is_on() << endl;
    // cout << id2 << ' ' << id2.is_on() << id2.is_set(1) << id2.is_set(0) << endl;

    if (id0.is_NIL()) { }
    if (id1.is_NIL()) { }
    if (id2.is_NIL()) { }


    id2.copy_id(id2);

}
