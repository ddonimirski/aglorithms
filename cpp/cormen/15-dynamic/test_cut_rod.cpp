#include <iostream>
#include <cassert>

using std::cout, std::cerr, std::endl, std::cin;

static const unsigned price[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

static constexpr unsigned N = sizeof(price)/sizeof(*price);
static unsigned split[N];
static unsigned result[N];

template<class CONT>
void pr(CONT const& cont) {
    for (auto const& v: cont) 
        cerr << v << ' ';
    cerr << '\n';
}

template<class P, class S, unsigned N>
void fill_cut_rod(P const (&p)[N], P (&r)[N], S (&s)[N], unsigned n) {
    //assert(n < N);

    s[0] = 0u;
    r[0] = 0;
    for (unsigned j = 1u; j <= n; ++j) {
        auto q = p[0];
        for (unsigned i = 1u; i <= j; ++i) {
            if (auto const pp = p[i] + r[j - i]; q < pp) {
                q = pp;
                s[j] = i;
            }
        }
        r[j] = q;
    }
}


template<class P, class S, unsigned N>
void pr_results(std::ostream& os, P const(&r)[N], S const (&s)[N], unsigned n) {
    //assert(n < N);

    os << "price: " << r[n] << " split: ";

    while (n > 0) {
        os << s[n];
        if (s[n] != n) os << ", ";
        n = n - s[n];
    }
    os << '\n';
}


int main() {

    fill_cut_rod(price, result, split, N-1);

    pr(result);
    pr(split);

    while (true) {
        unsigned n;
        // type 0 -> exit
        cin >> n;
        if (!n) break;
        assert(n < N);

        pr_results(cout, result, split, n);
    }

}
