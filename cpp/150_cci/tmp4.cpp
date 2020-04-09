#include <iostream>
#include <vector>
#include <numeric>

using std::cout, std::cerr, std::endl;
using std::vector;
using std::max;

auto cost(vector<int> const& B) noexcept {

    unsigned long long  mi = 0, m1 = 0;
    for (int i = 1; i < B.size(); ++i) {
        auto const ni = max(mi+abs(B[i] - B[i-1]), m1 + abs(B[i] - 1));
        m1 = max(mi+abs(1 - B[i-1]), m1);
        mi = ni;
        cerr << mi << ' ' << m1 << endl;
    }

    return max(mi, m1);
}

auto cost2(vector<int> const& B) noexcept {

    auto s0 = 0ull, s1 = 0ull;
    for (auto i = 1u; i < B.size(); ++i) {
        auto const t0 = max(s0, s1 + B[i-1] - 1);
        s1 = s0 + B[i] - 1;
        s0 = t0;
        cerr << s0 << ' ' << s1 << endl;
    }

    return max(s0, s1);
}


int main() {

    vector<int> B = {14, 30, 82, 49, 47, 96, 34, 66, 15, 11, 43, 45, 56, 77, 53, 13, 43, 92, 67, 37};
    //cout << cost(B) << endl;
    B = {39, 99, 55, 47, 17, 53, 86, 33, 95, 72, 45, 56};
    cout << cost(B) << endl;
    cout << cost2(B) << endl;


}
