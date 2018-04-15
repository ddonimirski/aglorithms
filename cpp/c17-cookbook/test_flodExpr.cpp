#include <iostream>

using namespace std;

template<typename ...Ts>
auto sum(Ts ...ts)
{
    return (ts + ...);
}

int main() {
    cout << sum(1,2,3,4,5,6) << endl;
}
