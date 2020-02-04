#include <iostream>

using std::cout, std::endl;


template<class T, int N=4000>
struct manager {

    constexpr static unsigned NIL = (unsigned) -1;
    constexpr static auto size = N;

    struct chunk {
        T val;
        unsigned next;
        unsigned prev;

        chunk() {}
        chunk(T&& v, unsigned p, unsigned n): val(v), next(n), prev(p) {}

        friend std::ostream& operator << (std::ostream& os, chunk const& v) {
            os << '(';
            if (v.prev == NIL)
                os << "NIL,";
            else
                os << v.prev << ',';
            if (v.next == NIL)
                os<< "NIL)";
            else
                os << v.next << ')';

            return os;
        }
    };

    unsigned head = NIL; 
    unsigned free = 0u;
    chunk arr[N];


    manager() {

        static_assert(N > 2, "N have to be greater then zero");

        arr[0].prev = NIL;
        arr[0].next = 1;

        for (unsigned int i = 1; i < N - 1; ++i)
        {
            arr[i].prev = i-1;
            arr[i].next = i+1;
        }

        arr[N-1].prev = N-2;
        arr[N-1].next = NIL;
    }


    T& operator[] (int i) {
        return arr[i].val;
    }

    T const& operator[] (int i) const {
        return arr[i].val;
    }

    unsigned allocate(T&& val)
    {
        if (free == NIL)
        {
            return NIL;
        }

        auto const curr = free;
        auto const prev = head;
        auto const curr_free = arr[free].next;

        //new (arr+free) chunk(val, head, NIL);
        if (head != NIL)
            arr[head].next = curr;
        arr[curr].val = val;
        arr[curr].prev = prev;
        arr[curr].next = NIL;
        head = curr;
        free = curr_free;
        arr[free].prev = NIL;

        return curr;
    }

    void deallocate(unsigned i) {
        if (head == NIL)
            return;


        if (head == i)
            head = arr[i].prev;

        if (arr[i].prev != NIL)
            arr[arr[i].prev].next = arr[i].next;
        if (arr[i].next != NIL)
            arr[arr[i].next].prev = arr[i].prev;

        arr[i].prev = NIL;
        arr[i].next = free;

        arr[free].prev = i;
        free = i;

    }


    friend std::ostream& operator << (std::ostream& os, manager const& mm) {

        os << "size: " << mm.size << endl;
        os << "head: " << mm.head << '\n';
        os << "free: " << mm.free << '\n';

        int i = 0;
        for (int i = 0; i < mm.size; ++i) {
            os << i << ' ' << mm.arr[i] << "  " << mm.arr[i].val << endl;
        }

        return os;
    }

};

template<class T, int N = 4000>
auto make_manager() {
    return manager<T, N>();
}


struct cc {
    int a;
    int b;

    friend std::ostream& operator << (std::ostream& os, cc const& v) {
        return os << "[" << v.a << ", " << v.b << "]";
    }
};

int main() {

    auto mm = make_manager<cc, 10>();

    int m = 0;

    m = mm.allocate({1,2});
    cout << "first allocated " << mm[m] << endl;

    m = mm.allocate({2,4});
    cout << "second allocated " << mm[m] << endl;
    cout << mm << endl;

    m = mm.allocate({5,6});
    cout << "third allocated " << mm[m] << endl;
    cout << mm << endl;

    mm.deallocate(m);
    cout << mm << endl;

    m = mm.allocate({7,8});
    cout << "forth allocated " << mm[m] << endl;
    cout << mm << endl;

}
