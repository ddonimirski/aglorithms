#if !defined AP_150_CCI_C03_E02
#define AP_150_CCI_C03_E02

#include <vector>

namespace a150_cci::c03::e02
{

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

} // namespace a150_cci::c03::e02


#endif // AP_150_CCI_C03_E02
