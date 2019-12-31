#if !defined RED_BLACK_BST_HPP
#define RED_BLACK_BST_HPP

#include <numeric>
#include <iostream>
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

        node(K& k, V& v, id_type p=id_type(), id_type l=id_type(), id_type r=id_type())
            : key{k}, val{v}, parent{p}, left{l}, right{r}
        {}

        bool is_red() const noexcept { return is_on(parent); }
        void set_red() noexcept { on(parent); } 
        void set_black() noexcept { off(parent); } 
        void copy_color(node const& n) noexcept { copy_on(n.parent, parent); }

        friend std::ostream& operator << (std::ostream& os, node const& n) {
            os << '[' << n.is_red() << ':' << n.parent << ' ' << n.left << ',' << n.right << ']' << ' ';
            return os << n.key << ':' << n.val; 
        }
    };

    id_type root;
    storage_type<node, N> storage;

    //red_black_bst() { }

    node& operator[] (id_type const& id) {
        return storage[id];
    }

    node const& operator[] (id_type const& id) const {
        return const_cast<red_black_bst&>(*this)[id];
    }

    void add(K&& k, V&& v) {

        if (is_NIL(root)) {

            auto const id = storage.alloc();
            storage[id] = node{k,v};

            root = id;
            return;
        }

        auto next = root;

        while (!is_NIL(next)) {

            if (storage[next].key < k) {
                if (is_NIL(storage[next].right)) {
                    auto const id = storage.alloc();
                    storage[id] = node{k,v};
                    storage[id].parent = next;
                    storage[next].right = id;
                    break;
                }
                next = storage[next].right;
            }
            else if (storage[next].key > k) {
                if (is_NIL(storage[next].left)) {
                    auto const id = storage.alloc();
                    storage[id] = node{k,v};
                    storage[id].parent = next;
                    storage[next].left = id;
                    break;
                }
                next = storage[next].left;
            }
            else {
                storage[next].val = v;
                break;
            }
        }
    }


    void rotate_left(id_type h) {
        auto& head = storage[h];
        auto const x  = head.right;
        auto& node = storage[x];

        head.right = node.left;
        head.parent = x;
        node.left = h;
        node.copy_color(head);
        head.set_red();

        if (h == root) {
            root = x;
            storage[root].parent = id_type{};
        }
    }

    void rotate_right(id_type h) {
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
