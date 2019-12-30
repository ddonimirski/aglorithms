#if !defined RED_BLACK_BST_HPP
#define RED_BLACK_BST_HPP

#include <numeric>
#include <iostream>

template<class V, class K=int, int N=20>
struct red_black_bst {

    struct node {
        constexpr static unsigned NIL = (((unsigned)-1)-1)>>1;

        K key;
        V val;

        unsigned id_left;
        unsigned id_right;
        unsigned id_parent;

        unsigned parent_id() const noexcept { return id_parent & NIL; }
        bool is_red() const noexcept { return id_parent & ~NIL; }

        friend std::ostream& operator << (std::ostream& os, node const& n) {
            //auto id = [&os](unsigned id) -> std::ostream& {
            //    if (id == NIL) os << "NIL";
            //    else           os << id;
            //    return os;
            //};
            //id(n.id_parent) << ',';
            //id(n.id_left) << ',';
            //id(n.id_right) << ' ';
            return os << n.key << ':' << n.val << ' '; 
        }
    };

    unsigned root = node::NIL;
    unsigned free = 0u;
    node storage[N];

    red_black_bst() {
        static_assert(N < node::NIL-2, "N must be lest then NIL");

        for (unsigned i = 0; i < N-1; ++i) {
            storage[i].id_parent = i+1;
        }
        storage[N-1].id_parent = node::NIL;
    }

    friend std::ostream& operator << (std::ostream& os, red_black_bst const& bst) {
        os << "red black storage\n";
        for (unsigned i = 0; i < N; ++i) {
            os << i << ' ' << bst.storage[i] << '\n';
        }
        return os;
    }

};

#endif  // RED_BLACK_BST_HPP
