#if !defined RED_BLACK_BST_HPP
#define RED_BLACK_BST_HPP

#include <numeric>
#include <iostream>
#include <cassert>
#include "storage.hpp"


template<class V, class K=int, unsigned N=20>
struct red_black_bst {

    struct node {
        id_type parent;
        id_type left;
        id_type right;

        K key;
        V val;

        node(): key{}, val{} {} // TODO: consider left not initialized

        node(K const& k, V const& v) : key{k}, val{v} { }

        node(node const& n): key{n.key}, val{n.val} {}

        bool is_red() const noexcept { return is_on(parent); }
        void set_red() noexcept { on(parent); } 
        void set_black() noexcept { off(parent); } 
        void copy_color(node const& n) noexcept { copy_flags(parent, n.parent); }

        friend std::ostream& operator << (std::ostream& os, node const& n) {
            os << '[' << n.is_red() << ':' << n.parent << ' ' << n.left << ',' << n.right << ']' << ' ';
            return os << n.key << ':' << n.val; 
        }
    };


    id_type root;
    storage_type<node, N> storage;

    // TODO: fancy constructors
    //red_black_bst() { }

    node& operator[] (id_type const& id) {
        return storage[id];
    }

    bool is_RED(id_type id) {
        if (is_NIL(id)) return false;
        return  storage[id].is_red();
    }

    node const& operator[] (id_type const& id) const {
        return const_cast<red_black_bst&>(*this)[id];
    }

    void add(K const& k, V const& v) {
        if (is_NIL(root)) {
            auto const id = storage.alloc();
            storage[id] = node{k, v};
            root = id;
            return;
        }

        set_root(add(root, k, v));
    }

    id_type add(id_type h, K const& k, V const& v) {
        if (is_NIL(h)) {
            auto const id = storage.alloc();
            storage[id] = node{k, v};
            // new node is always red :p
            storage[id].set_red();
            return id;
        }

        if (k < storage[h].key) {
            storage[h].left = add(storage[h].left, k, v);
            storage[storage[h].left].parent = h;
        } else if (k > storage[h].key) {
            storage[h].right = add(storage[h].right, k, v);
            storage[storage[h].right].parent = h;
        } else {
            storage[h].val = v;
        }


        if (is_RED(storage[h].right) && !is_RED(storage[h].left)) {
            h = rotate_left(h);
        }
        if (is_RED(storage[h].left) && is_RED(storage[storage[h].left].left)) {
            h = rotate_right(h);
        }
        if (is_RED(storage[h].right) && is_RED(storage[h].left)) {
            flip_color(h);
        }

        return h;
    }

    void set_root(id_type x) {
        // root always has NIL parent and black
        storage[x].parent.set_NIL();
        root = x;
    }

    id_type rotate_left(id_type h) {

        auto& head = storage[h];
        auto const x  = head.right;
        assert(!is_NIL(x));

        auto& node = storage[x];
        assert(node.is_red());

        head.right = node.left;
        head.parent = x;
        node.left = h;
        node.copy_color(head);
        head.set_red();

        return x;
    }


    id_type rotate_right(id_type h) {
        auto& head = storage[h];
        auto const x  = head.left;
        assert(!is_NIL(x));

        auto& node = storage[x];
        assert(node.is_red());

        head.left = node.right;
        head.parent = x;
        node.right = h;
        node.copy_color(head);
        head.set_red();

        return x;
    }

    void flip_color(id_type h) {
        auto& head = storage[h];
        assert(!is_NIL(head.left) && !is_NIL(head.right));

        auto& left_node = storage[head.left];
        auto& right_node = storage[head.right];

        assert(!head.is_red());
        assert(left_node.is_red());
        assert(right_node.is_red());

        head.set_red();
        left_node.set_black();
        right_node.set_black();
    }


    friend std::ostream& operator << (std::ostream& os, red_black_bst const& bst) {
        os << "red black storage\n";
        os << "root " << bst.root << '\n';
        for (id_type i = 0; i < N; ++i) {
            os << i << ' ' << bst[i] << '\n';
        }
        return os;
    }

};

#endif  // RED_BLACK_BST_HPP
