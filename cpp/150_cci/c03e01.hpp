#if !defined AP_150_CCI_C03_E01
#define AP_150_CCI_C03_E01

#include <iostream>
#include <vector>


namespace a150_cci::c03::e01
{


template<class T>
struct stacks {

    struct node {
        int next;
        T data;

        friend std::ostream& operator << (std::ostream& os, node const& n) {
            return os << '(' << n.next << ',' << n.data << ')' << ' ';
        }
    };

    static constexpr int capacity = 20;

    std::vector<node> storage;
    std::vector<int> stack_id;
    std::vector<int> stack_size;

    int num_stacks;
    int left = capacity;
    int free = 0;

    stacks(int num = 3): storage(capacity), stack_id(num), stack_size(num) {
        auto curr = 1;
        for (auto& v: storage) v.next = curr++;
        storage[capacity-1].next = -1;
        for (auto& v: stack_id) v = -1;
        for (auto& v: stack_size) v = 0;
    }

    bool is_empty(int s_id) const { return 0 == stack_size[s_id]; }
    bool size(int s_id) const { return stack_size[s_id]; }

    bool push(int s_id, T const& v) {
        if (free == -1 || s_id >= stack_id.size()) return false;
        auto const id = free;
        free = storage[id].next;
        auto const p_id = stack_id[s_id];
        stack_id[s_id] = id;
        storage[id] = { p_id, v };
        left--;
        return true;
    }

    T top(int s_id) const {
        if (stack_id[s_id] == -1 || s_id >= stack_id.size())
            throw int(-1);
        return storage[stack_id[s_id]].data;
    }

    bool pop(int s_id) {
        if (stack_id[s_id] == -1 || s_id >= stack_id.size()) return false;
        auto const id = stack_id[s_id];
        stack_id[s_id] = storage[id].next;
        storage[id].next = free;
        free = id;
        left++;
        return true;
    }

    friend std::ostream& operator << (std::ostream& os, stacks const& ss) {
        os << "storage: " ;
        for (auto& v: ss.storage) os << v << ' '; os << std::endl;
        os << "free: " << ss.free << std::endl;
        os << "stack_id: ";
        for (auto& v: ss.stack_id) os << v << ' '; os << std::endl;
        return os;
    }
};

} // namespace a150_cci::c03::e01

#if 0
int main() {
    stacks<int> ss;

    cerr << ss << std::endl;

    ss.push(0,1);
    ss.push(0,2);
    ss.push(1,3);
    ss.push(1,4);
    ss.push(2,5);
    ss.push(2,6);

    cout << ss.top(0) << std::endl;
    cout << ss.top(1) << std::endl;
    cout << ss.top(2) << std::endl;
    
    cerr << ss << std::endl;

    cout << ss.top(0) << std::endl;
    ss.pop(0);
    cout << ss.top(0) << std::endl;
    ss.pop(0);

    //cout << ss.top(0) << std::endl;
    cout << ss.top(1) << std::endl;
    cout << ss.top(2) << std::endl;
    

    cerr << ss << std::endl;
    
}
#endif

#endif // AP_150_CCI_C03_E01
