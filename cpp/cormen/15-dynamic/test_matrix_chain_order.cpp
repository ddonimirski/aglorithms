#include <cassert>
#include <iostream>

using std::cout, std::cerr, std::endl, std::cin;

const unsigned p[] = {30, 35, 15, 5, 10, 20, 25, 1};

constexpr unsigned MAX = sizeof(p)/sizeof(*p) - 1;
static_assert(MAX>2);

static unsigned m[MAX][MAX];
static unsigned s[MAX][MAX];


template<class T, int MAX>
void pr_m(T const (&arr)[MAX][MAX], unsigned n = MAX) {
    cerr << "print:" << endl;
    for (unsigned i = 0u; i < n; ++i) {
        for (auto j = i; j < n; ++j) {
            cerr << arr[i][j] << ',';
        }
        cerr << '\n';
    }
}


void print_matrixes(unsigned const (&m)[MAX+1], unsigned n = MAX) {
    assert(n > 1 && n <= MAX);
    cout << "matrixes shapes A[COLxROW]: ";
    for (unsigned i = 0; i < n; ++i) {
        cout << 'A' << i+1 << '[' << m[i] << 'x' << m[i+1] << "] ";
    }
    cout << '\n';
}


void matrix_chain_order(unsigned n = MAX) {
    assert(n > 1 && n <= MAX);

    auto init_m = [](unsigned n) {
        for (unsigned i = 0u; i < n; ++i)
            m[i][i] = 0;
    };

    init_m(n);

    for (unsigned l = 2u; l <= n; ++l) {
        for (unsigned i = 0u; i <= n-l; ++i) {
            auto j = i + l - 1;
            m[i][j] = -1;
            for (unsigned k = i; k <= j; ++k) {
                auto const q = m[i][k] + m[k+1][j] + p[i]*p[k+1]*p[j+1];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}


unsigned matrix_chain_rec(unsigned i, unsigned j = MAX) {
    if (m[i][j] < (unsigned)-1) return m[i][j];
    if (i == j) return 0;
    m[i][j] = (unsigned)-1;
    
    for (unsigned k = i; k < j; ++k) {
        auto const q = matrix_chain_rec(i, k)
                     + matrix_chain_rec(k+1, j)
                     + p[i]*p[k+1]*p[j+1];
        if (q < m[i][j]) {
            m[i][j] = q;
            s[i][j] = k;
        }
    }

    return m[i][j];
}

void matrix_chain_order_rec(unsigned n) {
    assert(n > 1 && n <= MAX);

    auto init_m = [](unsigned n) {
        for (auto& row: m)
            for (auto& v: row)
                v = (unsigned)-1;
    };

    init_m(n);
    matrix_chain_rec(0u, n);
}


void print_optimal_parens(unsigned (&s)[MAX][MAX], unsigned i, unsigned j) {
    assert(i<= MAX && j <= MAX);
    if (j==i) {
        cout << 'A' << i + 1 ;
    }
    else {
        cout << '(';
        print_optimal_parens(s, i, s[i][j]);
        cout << ' ';
        print_optimal_parens(s, s[i][j]+1, j);
        cout << ')';
    }
}


// TODO: implemtation of real multiply (? base on print_optimal_parens)

int main() {

    // TODO: add reading matrix sizes from file or something

    cout << "set number of matrixes to consider (MAX " << MAX << "): ";
    int n;
    cin >> n;

    if (n > MAX) {
        cerr << "there is only 6 matrixes in the chain\n";
        exit(-1);
    }

    print_matrixes(p, n);

    cout << "bottom up\n";
    matrix_chain_order(n);
    print_optimal_parens(s, 0, n-1);
    cout << endl;

    cout << "recurcive\n";
    matrix_chain_rec(0, n);
    print_optimal_parens(s, 0, n-1);
    cout << endl;
}
