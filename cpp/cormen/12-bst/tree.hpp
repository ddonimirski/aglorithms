#if !defined TREE_HPP
#define TREE_HPP

#include <iostream>

template<class T, unsigned N = 1000>
struct tree_us {

    constexpr static unsigned NIL = (unsigned) -1;

    struct Node {
        T val;
        unsigned parent;
        unsigned left;
        unsigned right;

        friend std::ostream& operator << (std::ostream& os, Node const& n) {
            os << n.val << '(';
            if (n.parent == NIL)
                os << "NIL ";
            else
                os << n.parent << ' ';
            if (n.left == NIL)
                os << "NIL ";
            else
                os << n.left << ' ';
            if (n.right == NIL)
                os << "NIL)";
            else
                os << n.right << ')';

            return os;
        }

    };

    Node storage[N];
    unsigned root;
    unsigned free;

    tree_us(): root{NIL}, free{0u} {

        static_assert(N < NIL, "N must be lest then NIL");

        for (unsigned i = 0; i < N-1; ++i) {
            storage[i].parent = i+1;
            storage[i].left = storage[i].right = NIL;
            storage[i].val = 0;
        }
        storage[N-1].left = storage[N-1].right = NIL;
        storage[N-1].val = 0;
    }

    friend std::ostream& operator << (std::ostream& os, tree_us const& tt) {
        os << "free: " << tt.free << '\n';
        os << "root: " << tt.root << '\n';
        int i = 0;
        for (auto const& v: tt.storage) {
            os << i++ << ':' << v << '\n';
        }
        return os;
    }

    void print() {
        std::cout << "root ";
        if (root == NIL)
            std::cout << "NIL";

        print_bfs(root, 0);
    }

    void print_dfs(unsigned id, int level) {
    }

    void print_bfs(unsigned id, int level) {
        if (id == NIL) {
            std::cout << "NIL";
            return;
        }
        
        std::cout << "level (" << level << ") ";
        std::cout << storage[id].val << " left ";
        print(storage[id].left, level + 1);
        std::cout << " right ";
        print(storage[id].right, level + 1);
        std::cout << std::endl;
    }


    int add(T&& v) {

        if (free == NIL) {
            return NIL;
        }

        if (root == NIL) {
            std::cout << "add root\n";
            root = free;    
            free = storage[free].parent;
            storage[root].parent = NIL;
            storage[root].val = v;
            return root;
        }

        auto next = root;

        while (next != NIL) {
            if (storage[next].val > v) {
                if (storage[next].left != NIL) {
                    next = storage[next].left;
                } else {
                    auto const next_free = storage[free].parent;
                    storage[next].left = free;
                    storage[free].parent = next;
                    storage[free].val = v;
                    free = next_free;
                    break;
                }
            } else if (storage[next].val < v) {
                if (storage[next].right != NIL) {
                    next = storage[next].right;
                } else {
                    auto const next_free = storage[free].parent;
                    storage[next].right = free;
                    storage[free].parent = next;
                    storage[free].val = v;
                    free = next_free;
                    break;
                }
            } else {
                storage[next].val = v;
                break;
            }
        }


        return next;
    }
};


#endif
