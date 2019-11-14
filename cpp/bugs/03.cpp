// compile paramterers: g++ -O2
#include <iostream>

using namespace std;


void pr(int v);


int main()
{
    char mc[] = {1, 2 ,3 ,4};
    int c = 0;
    for (int iv = 0; iv < 4; iv++, pr(mc[iv])) // infinit loop with -O2
    {
        c += mc[iv];
        pr(c);
    }

    cout << c << endl;
}


void pr(int v)
{
    cout << v << endl;
}

