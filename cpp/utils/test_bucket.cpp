#include "bucket.hpp"
#include <iostream>
#include <cassert>
#include "gtest/gtest.h"

TEST(bucket, creation) {

    bucket<int> bb;

    bb.insert(1);
    bb.insert(2);
    bb.insert(3);
    bb.insert(4);
    bb.insert(5);
    bb.insert(6);

    bb.erase(0);
    bb.erase(0);
    
}
