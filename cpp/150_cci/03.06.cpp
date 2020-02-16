#include <iostream>
#include <cassert>
#include <vector>

using std::cout, std::cerr , std::endl;
using std::cin;
using std::vector;

template<class T>
struct stack {
    std::vector<T> storage;
    int curr_top = -1;

    //stack():storage(capacity) {}

    T const& top() const {
        if (curr_top == -1) throw int(-1);
        return storage[curr_top];
    }

    T pop() {
        if (curr_top == -1) {  cerr << "empty pop " << curr_top << endl; throw int(-1); }
        return storage[curr_top--];
    }

    void push(T const& v) {
        if (curr_top + 1 == storage.size()) {
            storage.push_back(v);
            curr_top++;
        }
        else {
            storage[++curr_top] = v;
        }
    }

    bool is_empty() const {
        return curr_top == -1;
    }

    size_t size() const {
        return curr_top + 1;
    }


    friend std::ostream& operator << (std::ostream& os, stack const& s) {
        os << "curr_top: " << s.curr_top << '\n';
        for (size_t i = 0; i < 10; ++i) os << s.storage[i] << ' ';
        return os << '\n';
    }
};



template<class T>
auto sort(stack<T>& s) {
    stack<T> r;

    while (!s.is_empty()) {
        auto const t = s.pop();
        cerr << t << endl;
        while (!r.is_empty() && t < r.top()) {
             s.push(r.pop());
        }
        r.push(t);
    }

    return r;
}

int main() {

    stack<int> s;

    // int n;
    // cin >> n;
    // while (n--) {
    //     int v;
    //     cin >> v;
    //     s.push(v);
    // }

    vector vec = {1, 5, 2, 6, 7, 9, 0, 3, 8, 4};

    for (auto v: vec) s.push(v);

    while (!s.is_empty()) cout << s.pop() << ' ';
    cout << endl;

    for (auto v: vec) s.push(v);

    cout << sort(s) << endl;

    return 0;
}
