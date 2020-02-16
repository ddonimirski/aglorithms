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
struct queue {
    stack<T> in;
    stack<T> out;

    size_t size() const { return in.size() + out.size(); }

    void move_out() { while (!in.is_empty()) out.push(in.pop()); }

    T const& peek() const {
        if (out.empty()) move_out();
        return out.top();
    }

    T remove() {
        if (out.is_empty()) move_out();
        return out.pop();
    }

    void add(T const& v) {
        in.push(v);
    }
};

int main() {

    queue<int> q;

    q.add(1);
    q.add(2);
    q.add(3);

    cout << q.remove() << endl;

    q.add(4);
    q.add(5);
    q.add(6);
    q.add(7);

    cout << q.remove() << endl;
    cout << q.remove() << endl;
    cout << q.remove() << endl;
    cout << q.remove() << endl;

    q.add(8);
    q.add(9);
    q.add(10);
    q.add(11);

    while(q.size())
        cout << q.remove() << endl;
}
