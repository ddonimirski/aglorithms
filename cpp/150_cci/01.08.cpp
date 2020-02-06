#include <iostream>
#include <vector>
#include <cassert>
#include <string>


using std::cout, std::cerr , std::endl;
using std::cin;
using std::string;

bool is_rotate(string const& s1, string const& s2) {

    string s(s2+s2);

    return string::npos != s.find(s1);
}

int main() {

    string s1, s2;

    cin >> s1 >> s2;

    cout << (is_rotate(s1, s2)?"tak":"nie") << endl;
}

