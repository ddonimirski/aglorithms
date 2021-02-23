#if !defined AP_150_CCI_C03_E06
#define AP_150_CCI_C03_E06

#include <iostream>
#include <vector>


template<class T>
struct ddstack {
    std::vector<T> storage;
    int curr_top = -1;

    //ddstack():storage(capacity) {}

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


    friend std::ostream& operator << (std::ostream& os, ddstack const& s) {
        os << "curr_top: " << s.curr_top << '\n';
        for (size_t i = 0; i < 10; ++i) os << s.storage[i] << ' ';
        return os << '\n';
    }
};



template<class T>
auto sort(ddstack<T>& s) {
    ddstack<T> r;

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

#if 0
int main() {

    ddstack<int> s;

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
#endif

#endif // AP_150_CCI_C03_E06
