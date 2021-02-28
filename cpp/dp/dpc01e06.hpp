#if !defined DP_CH01_E06
#define DP_CH01_E06

#include <ostream>

//
// s, d, c - tree pegs
// n - number of disk
namespace dp::ch01::e06
{

void towerOfHanoi(std::ostream& os, char s, char d, char e, int n) {

    if (n <= 0) return;

    towerOfHanoi(os, s, e, d, n-1);
    os << "move disk " << n << " from " << s << " to " << d << '\n';
    towerOfHanoi(os, e, d, s, n-1);
}

} // namespace dp::ch01::e06

#endif // DP_CH01_E06
