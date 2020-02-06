#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <cstring>

using std::cout, std::cerr , std::endl;
using std::vector;
using std::string;

int remove_duplicates(char* s, size_t len) {

    auto tail = 1u;
    for (auto i = 1u, j = 0u; i < len; ++i) {
        for (j = 0; j < tail; ++j) {
            if (s[i] == s[j]) {
                break;
            }
        }
        if (j == tail) {
            s[tail++] = s[i];
        }
    }

    s[tail] = 0;
    return tail;
}


int remove_duplicates(string& s) {

    auto tail = 1u;
    auto len = s.size();
    for (auto i = 1u, j = 0u; i < len; ++i) {
        for (j = 0; j < tail; ++j) {
            if (s[i] == s[j]) {
                break;
            }
        }
        if (j == tail) {
            s[tail++] = s[i];
        }
    }

    s.resize(tail);
    return tail;
}

int main() {

    char s[] = "nnogonana";
    string str(s);

    //cout << remove_duplicates(s, strlen(s)) << endl;
    cout << remove_duplicates(str) << endl;




    cout << str << endl;
    
}
