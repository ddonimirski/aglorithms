// compile paramterers: g++-8 -O2
#include <iostream>
#include <limits>

int add_no_overflow(int a, int b)
{
    if (a < 0) return -1;
    if (b < 0) return -1;
    if (a+b < 0) return -1; // not checked with -O2
    return a+b;
}

int add_no_overflow2(int a, int b)
{
    if (a < 0 || b < 0 || a+b < 0) return -1;
    return a+b;
}


using namespace std;

int main()
{
    int a = numeric_limits<int>::max();
    int b = 1024;

    cout << add_no_overflow(a, b) << endl;
    cout << add_no_overflow2(a, b) << endl;
}
