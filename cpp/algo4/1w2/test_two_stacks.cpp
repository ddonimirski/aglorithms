#include "two_stacks.h"
#include <string>
#include <cassert>


int main() {
    {//to_int
        std::string str = "12345";
        int s = 0;
        assert(to_int(str, s) == 12345);
        assert(s == str.size()-1);
        s = 0;
        char const* cstr = "12345";
        assert(to_int(cstr, s) == 12345);
        assert(s == 4);
        s = 2;
        str = "  123";
        assert(to_int(str, s) == 123);
        assert(s == str.size()-1);
        str = "  923 ";
        s = 2;
        assert(to_int(str, s) == 923);
        assert(s == str.size()-2);
        str = "  923+";
        s = 2;
        assert(to_int(str, s) == 923);
        assert(s == str.size()-2);
    }
    { //two_stacks
        std::string str = "(1 + 2)";
        auto v = two_stacks(str);
        assert(v == 3);
        str = "(3*(1+2))+1";
        v = two_stacks(str);
        assert(v == 10);
    }
}

