#include <iostream>
#include <vector>
#include <cassert>

using std::cout, std::cerr, std::endl;

// s, d, c - tree pegs
// n - number of disk

void towerOfHanoi(char s, char d, char e, int n) {

    if (n <= 0) return;

    towerOfHanoi(s, e, d, n-1);
    cout << "move disk " << n << " from " << s << " to " << d << endl;
    towerOfHanoi(e, d, s, n-1);
}

int main() {

    towerOfHanoi('s', 'd', 'e', 3);
}


