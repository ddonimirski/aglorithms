#include <iostream>
#include <cassert>
#include <vector>

using std::cout, std::cerr , std::endl;
using std::cin;
using std::vector;


template<class T>
struct stack_with_min {
    struct min_count {
        T min_value;
        size_t count;

        friend std::ostream& operator << (std::ostream& os, min_count const& v) {
            return os << '(' << v.min_value << ',' << v.count << ')';
        }
    };

    std::vector<min_count> min_storage;
    std::vector<T> storage;
    int curr_top;
    int curr_min;

    stack_with_min(): curr_top(-1), curr_min(-1) {}

    void push(T const& v) {
        if (curr_top + 1 == storage.size()) {
            storage.push_back(v);
        } else {
            storage[curr_top] = v;
        }
        ++curr_top;
        
        if (T c_min; curr_min == -1 || v <= (c_min = min()))  {
            if (curr_min + 1 == min_storage.size()) {
                min_storage.push_back({v, 1});
                curr_min++;
            } else if (c_min == v) {
                min_storage[curr_min].count++;
            } else {
                min_storage[curr_min++] = {v, 1};
            }
        }
    }

    T const& min() const {
        if (curr_min == -1) throw int(-1);
        return min_storage[curr_min].min_value;
    }

    T const& top() const {
        if (curr_top == -1) throw int(-1);
        return storage[curr_top];
    }

    void pop() {
        // destroy or not left element
        if (top() == min()) {
            min_storage[curr_min].count--;
            if (min_storage[curr_min].count == 0) {
                curr_min--;
            }
        }
        curr_top--;
    }
};

int main() {

    stack_with_min<int> sm;

    sm.push(1);
    sm.push(2);
    sm.push(1);
    sm.push(0);
    sm.push(0);
    sm.push(0);
    sm.push(-1);
    sm.push(3);

    cerr << sm.top() << endl;
    cerr << sm.min() << endl;

    sm.pop();
    cerr << sm.top() << endl;
    cerr << sm.min() << endl;

    sm.pop();
    cerr << sm.top() << endl;
    cerr << sm.min() << endl;

    sm.pop();
    sm.pop();
    sm.pop();
    sm.pop();
    cerr << sm.top() << endl;
    cerr << sm.min() << endl;
}
