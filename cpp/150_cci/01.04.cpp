#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <cctype>
#include <cstring>

using std::cout, std::cerr , std::endl;
using std::vector;
using std::string;



bool is_anagram(string const& s1, string const& s2) {

    int c['z'-'a'+1];
    constexpr auto c_len = sizeof(c)/sizeof(*c);

    for (auto& v: c) v = 0;

    for (auto const v: s1) ++c[std::tolower(v)-'a'];

    for (auto const v: s2) --c[std::tolower(v)-'a'];

    int s = 0;
    for (auto const v: c) s += std::abs(v);

    return !s;
}

int main() {


    string s1 = "nowab";
    string s2 = "wano";

    cout << (is_anagram(s1, s2)?"tak":"nie") << endl;
}
