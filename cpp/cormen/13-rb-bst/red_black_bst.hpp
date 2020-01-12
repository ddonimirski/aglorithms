#if !defined RED_BLACK_BST_HPP
#define RED_BLACK_BST_HPP

#include <numeric>
#include <iostream>
#include <cassert>
#include <vector>
#include "storage.hpp"


template<class V, class K=int, int N = 20>
struct red_black_bst {

    using id_type = id_ui1f_type;

    struct node {
        id_type parent;
        id_type left;
        id_type right;

        K key;
        V val;

        node(): key{}, val{} {} // TODO: consider left not initialized

        node(K const& k, V const& v) : key{k}, val{v} { }

        node(node const& n): key{n.key}, val{n.val} {}

        bool is_red() const noexcept { return parent.is_on(); }
        void set_red() noexcept { parent.on(); } 
        void set_black() noexcept { parent.off(); } 
        void flip_color() noexcept { parent.flip_flags(); } 
        void copy_color(node const& n) noexcept { parent.copy_flags(n.parent); }

        friend std::ostream& operator << (std::ostream& os, node const& n) {
            os << '[' << n.is_red() << ':' << n.parent << ' ' << n.left << ',' << n.right << ']' << ' ';
            return os << n.key << ':' << n.val; 
        }
    };

    template<class T>
        using array20 = std::array<T, N>;

    id_type root;
    storage_type<node, array20, id_type> storage;

    // TODO: fancy constructors
    //red_black_bst() { }

    node& operator[] (id_type const& id) {
        return storage[id];
    }

    node const& operator[] (id_type const& id) const {
        return storage[id];
    }



//
//    node const& operator[] (id_type const& id) const {
//        return const_cast<red_black_bst&>(*this)[id];
//    }

    bool is_RED(id_type id) {
        if (id.is_NIL()) return false;
        return  storage[id].is_red();
    }

    void set_root(id_type x) {
        // root always has NIL parent and black
        storage[x].parent.set_NIL();
        root = x;
    }

////--------- add - based on algo4 - left red
    void add(K const& k, V const& v) {
        if (root.is_NIL()) {
            auto const id = storage.alloc();
            storage[id] = node{k, v};
            root = id;
            return;
        }

        set_root(add(root, k, v));
    }

    id_type add(id_type h, K const& k, V const& v) {
        if (h.is_NIL()) {
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
            flip_colors(h);
        }

        return h;
    }


    void del(K const& k) {
        //TODO: add checking if tree contains  the key
        
        // if both children of root are black, set root to red
        if (!is_RED(storage[root].left) && !is_RED(storage[root].right)) {
            storage[root].set_red();
        }

        // back to normal :P
        set_root(del(root, k));
    }


    id_type del(id_type h, K const& k) {
        if (k < storage[h].key) {
            if (!is_RED(storage[h].left) && !is_RED(storage[storage[h].left].left)) {
                h = mv_red_left(h);
            }
            storage[h].left = del(storage[h].left, k);
        }
        else {
            if (is_RED(storage[h].left)) {
                h = rotate_left(storage[h].left);
            }
            if (k == storage[h].key && storage[h].rightis_NIL()) {
                return id_type{};
            }
            if (!is_RED(storage[h].right) && !is_RED(storage[storage[h].right].left)) {
                h = mv_red_right(h);
            }
            if (k == storage[h].key == 0) {

                storage[h].right = del_min(storage[h].right);
            }
            else {
                storage[h].right = del(storage[h].right, k);
            }
        }
        return balance(h);
    }

    id_type rotate_left(id_type h) {

        auto& head = storage[h];
        auto const x  = head.right;
        assert(!x.is_NIL());

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
        assert(!x.is_NIL());

        auto& node = storage[x];
        assert(node.is_red());

        head.left = node.right;
        head.parent = x;
        node.right = h;
        node.copy_color(head);
        head.set_red();

        return x;
    }

    void flip_colors(id_type h) {
        auto& head = storage[h];
        assert(!head.left.is_NIL() && !head.right.is_NIL());

        auto& left_node = storage[head.left];
        auto& right_node = storage[head.right];

        //assert(!head.is_red());
        //assert(left_node.is_red());
        //assert(right_node.is_red());

        //head.set_red();
        //left_node.set_black();
        //right_node.set_black();
        head.flip_color();
        left_node.flip_color();
        right_node.flip_color();
    }


    id_type del_min(id_type h) {
        return h;
    }

    id_type del_max(id_type h) {
        return h;
    }

    id_type balance(id_type h) {
        if (is_RED(storage[h].right)) {
            h = rotate_left(h);
        }
        if (is_RED(storage[h].left) && id_RED(storage[storage[h].left].left)) {
            h = rotate_right(h);
        }
        if (is_RED(storage[h].left) && is_RED(storage[h].right)) {
            flip_colors(h);
        }
        return h;
    }


    id_type mv_red_left(id_type h) {
        // assert (h != NIL);
        // is_RED(h) && !is_RED(storage[h].left) && 
        flip_colors(h);
        if (is_RED(storage[storage[h].right].left)) {
            storage[h].right = rotate_right(storage[h].right);
            h = rotate_left(h);
            flip_colors(h);
        }
        return h;
    }

    id_type mv_red_right(id_type h) {
        flip_colors(h);
        if (is_RED(storage[storage[h].left].left)) {
            h = rotate_right(h);
            flip_colors(h);
        }
        return h;
    }

/////// ---------------------- insert - cormen -------------
    void insert(K const& k, V const& v) {


        auto  id = storage.alloc();
        storage[id] = node{k, v};

        id_type y;
        id_type x = root;

        while (!x.is_NIL()) {
            y = x;
            if (k < storage[x].key) {
                x = storage[x].left;
            } else {
                x = storage[x].right;
            }
        }

        if (!y.is_NIL()) {
            (k < storage[y].key ? storage[y].left:storage[y].right) = id;
            storage[id].parent = y; 
            storage[id].set_red();
            id = insert_fix(id, y);
        }

        set_root(id);
    }

    auto insert_fix(id_type z, id_type p) {
        auto r = root;
        id_type y;

        while (is_RED(p) && !storage[p].parent.is_NIL()) {
            if (storage[p].parent.left == p) { // parent on left
                y = storage[p].parent.right;
                if (is_RED(y)) {

                }
            }
            else { // parent on right

            }
        }

        return r;
    }



    void erase(K const& k) {
    }

    void erase_fix(id_type z) {
    }


//---------------------------------------------------------



    K min() const {
        if (auto const id = min(root); !id.is_NIL()) {
            return storage[id].key;
        }

        //TODO: throw
        return K{};
    }

    id_type min(id_type h) const {
        assert(!h.is_NIL());
        if (storage[h].left.is_NIL()) return h;
        return min(storage[h].left);
    }

    K max() const {
        if (auto const id = max(root); !id.is_NIL()) {
            return storage[id].key;
        }

        //TODO: throw
        return K{};
    }

    id_type max(id_type h) const {
        assert(!h.is_NIL());
        if (storage[h].right.is_NIL()) return h;
        return max(storage[h].right);
    }


    friend std::ostream& operator << (std::ostream& os, red_black_bst const& bst) {
        os << "red black storage\n";
        os << "root " << bst.root << '\n';
        for (id_type i = 0; i < bst.storage.arr.size(); ++i) {
            os << i << ' ' << bst[i] << '\n';
        }
        return os;
    }

};

#endif  // RED_BLACK_BST_HPP
