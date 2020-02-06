#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <cctype>
#include <cstring>

using std::cout, std::cerr , std::endl;
using std::vector;
using std::string;

string replace_space(string& s) {

    auto cs = 0u;
    auto s_len = s.size();

    for (auto const v: s) cs += (v == ' ');
    cerr << "spaces: " << cs << endl;

    auto const n_len = s_len + 2 * cs;
    if (s_len == n_len) return s;

    s.resize(n_len, '\0');
    for (int i = n_len-1 ; i >= 0; ) {
        if (s[--s_len] == ' ') {
            s[i--] = '0';
            s[i--] = '2';
            s[i--] = '%';
            continue;
        }
        s[i--] = s[s_len];
    }

    return s;
}

int main() {

    string s = " mowa trawa dupa ";

    cout << (s = replace_space(s)) << endl;
    cout << s.size() << endl;

}
