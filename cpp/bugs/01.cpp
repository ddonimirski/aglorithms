// compile paramterers: g++-8 -std=c++17 
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector vec{1,2,3,4};
    for (auto iv=vec.size()-1; iv>=0; --iv) //iv -> unsigned
        cout << vec[iv] << endl;
}
