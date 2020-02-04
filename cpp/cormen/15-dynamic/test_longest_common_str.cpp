#include <cassert>
#include <iostream>

using std::cout, std::cerr, std::endl, std::cin;

#include <string>
#include <algorithm>

constexpr unsigned MAX = 10;

unsigned c[MAX][MAX];

void pr(std::string const& X, std::string const& Y, unsigned (&c)[MAX][MAX]) {
    cout << "    ";
    for (unsigned i = 0; i < Y.size(); ++i) {
        cout << Y[i] << ' ';
    }
    cout << '\n';
    for (unsigned i = 0; i <= X.size(); ++i) {
        for (unsigned j = 0; j <= Y.size(); ++j) {
            if (j == 0) {
               if (i != 0) cout << X[i-1] << ' ';
               else cout << "  ";
            }
            cout << c[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

unsigned lcs_length(std::string const& X, std::string const& Y) {

    for (unsigned i = 0; i <= X.size(); ++i) c[i][0] = 0;
    for (unsigned j = 0; j <= Y.size(); ++j) c[0][j] = 0;

    for (unsigned i = 1; i <= X.size(); ++i) {
        for (unsigned j = 1; j <= Y.size(); ++j) {
            if (X[i-1] == Y[j-1]) {
                c[i][j] = c[i-1][j-1]+1;
            }
            else {
               c[i][j] = std::max(c[i-1][j], c[i][j-1]);
            }
        }
    }

    return c[X.size()][Y.size()];
}


unsigned lcs_len_rec(std::string const& X, unsigned i, std::string const& Y, unsigned j) {
    if (i == 0 || j == 0) {
        c[i][j] = 0;
    }
    else if (X[i] == Y[j]) {
        c[i][j] = 1 + lcs_len_rec(X, i-1, Y, j-1);
    }
    else {
       c[i][j] = std::max(lcs_len_rec(X, i-1, Y, j), lcs_len_rec(X, i, Y, j-1));
    }
    return c[i][j];
}

unsigned lcs_length_rec(std::string const& X, std::string const& Y) {
    return lcs_len_rec(X, X.size(), Y, Y.size());
}

int main() {

    std::string str1, str2;

    //cin >> str1;
    //cin >> str2;
    
    str1 = "BDCABA";
    str2 = "ABCBDAB";

    cout << lcs_length_rec(str1, str2) << endl;
    pr(str1, str2, c);

    cout << lcs_length(str1, str2) << endl;
    pr(str1, str2, c);
}
