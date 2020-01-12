#if !defined RB_BST_HPP
#define RB_BST_HPP

#include <numeric>
#include <iostream>
#include <cassert>
#include <vector>
#include "storage.hpp"


/////// ---------------------- insert - cormen -------------
template<class V, class K=int, int N = 20>
struct rb_bst {

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
    //rb_bst() { }

    node& operator[] (id_type const& id) {
        return storage[id];
    }

    node const& operator[] (id_type const& id) const {
        return storage[id];
    }

    bool is_RED(id_type id) {
        if (id.is_NIL()) return false;
        return  storage[id].is_red();
    }

    void set_root(id_type x) {
        // root always has NIL parent and black
        storage[x].parent.set_NIL();
        //storage[x].parent = {}; // save color
        root = x;
    }


    void insert(K const& k, V const& v) {
        auto  id = storage.alloc();
        storage[id] = node{k, v};

        std::cout << "add " << id << ' ' << storage[id] << '\n';

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

    auto insert_fix(id_type z, id_type zp) {
        while (is_RED(zp)) {
            auto zpp = storage[zp].parent;
            if (storage[zpp].left == zp) { // parent on left
                auto const s = storage[zpp].right;
                if (is_RED(s)) {
                    storage[zp].set_black();
                    storage[s].set_black();
                    storage[zpp].set_red();
                    z = zpp; /// got to next
                }
                else {
                    if (z == storage[zp].right) {
                        z = zp;
                        left_rotate(z);
                        zp = storage[z].parent; // update after rotation
                        zpp = storage[zp].parent; // update after roation
                    }
                    storage[zp].set_black();
                    storage[storage[zp].parent].set_red();
                    right_rotate(zpp);
                }
            }
            else { // parent on right
                auto const s = storage[zpp].left;
                if (is_RED(s)) {
                    storage[zp].set_black();
                    storage[s].set_black();
                    storage[zpp].set_red();
                    z = zpp;
                }
                else {
                    if (z == storage[storage[z].parent].left) {
                        z = zp;
                        right_rotate(z);
                        zp = storage[z].parent; // update after rotation
                        zpp = storage[zp].parent; // update after rotation
                    }
                    storage[zp].set_black();
                    storage[zpp].set_red();
                    left_rotate(zpp);
                }
            }
            zp = storage[z].parent;
        }

        return root;
    }


    void erase(K const& k) {
    }

    void erase_fix(id_type z) {
    }

    void update_head_parent(node& head, id_type h, id_type c) {
        if (head.parent.is_NIL()) {
            //set_root(c);
            storage[c].parent = {};
            root = c;
        } else {
            if (h == storage[head.parent].left)   /// is left child
                storage[head.parent].left  = c;

            else  // so it was right child
                storage[head.parent].right  = c;
        }

        head.parent = c;
    }

    void left_rotate(id_type x) {
        auto& head = storage[x];
        std::cerr << "left rotage " << x << " " << head << '\n';
        auto const y  = head.right;

        assert(!y.is_NIL());
        auto& node = storage[y];

        head.right = node.left;
        if (!node.left.is_NIL()) { // set for left x parent : parent was changed
            storage[node.left].parent = x;
        }

        node.parent = head.parent; // copy head parent
        update_head_parent(head, x, y);
        node.left = x;
    }

    void right_rotate(id_type y) {
        auto& head = storage[y];
        std::cerr << "right rotage " << y << " " << head << '\n';
        auto const x  = head.left;

        assert(!x.is_NIL());
        auto& node = storage[x];

        head.left = node.right;
        if (!node.right.is_NIL()) { // set for left x parent : parent was changed
            storage[node.right].parent = y;
        }

        node.parent = head.parent; // copy head parent
        update_head_parent(head, y, x);
        node.right = y;
    }

    void transplant(id_type u, id_type v) {
        auto& u_node = storage[u];
        if (u_node.parent.is_NIL()) {
            set_root(v);
        } else {
            auto& u_parent = storage[u_node.parent];
            (u == u_parent.left ? u_parent.left : u_parent.right) = v;
        }
        storage[v].parent = u_node.parent;
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


    friend std::ostream& operator << (std::ostream& os, rb_bst const& bst) {
        os << "red black storage\n";
        os << "root " << bst.root << '\n';
        for (id_type i = 0; i < bst.storage.arr.size(); ++i) {
            os << i << ' ' << bst[i] << '\n';
        }
        return os;
    }

};

#endif  // RB_BST_HPP
