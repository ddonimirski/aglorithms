#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <limits>

#include "matrix.hpp"

using std::cout, std::cerr, std::endl;
using std::cin;
using std::vector;

// combination
int C(int n, int m) {
    if (n == 0 || m == 0 || n == m) return 1;
    return C(n-1, m) + C(n-1, m-1);
}

constexpr int MAX = 20;

int Cm(int n, int m) {

    assert(n>=0 && m>=0 && n < MAX && m < MAX);

    static matrix<int> mm(MAX, MAX);

    if (n == 0 || m == 0 || n == m) return 1;

    if (mm[n][m] == 0) {
        mm[n][m] = C(n-1, m) + C(n-1, m-1);
    }

    return mm[n][m];
}

int Cit(int n, int m) {

    assert(n>=0 && m>=0 && n < MAX && m < MAX);

    static matrix<int> mm(MAX, MAX);

    for (int n = 0; n
}


int main() {
    int N;
    cin >> N;

    for (int n = 0; n <= N; ++n) {
        for (int m = 0; m <= n; ++m) {
            cout << C(n, m) << ' ';
        }
        cout << '\n';
    }

    for (int n = 0; n <= N; ++n) {
        for (int m = 0; m <= n; ++m) {
            cout << Cm(n, m) << ' ';
        }
        cout << '\n';
    }


    return 0;
}
