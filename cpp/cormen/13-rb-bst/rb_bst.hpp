#if !defined RB_BST_HPP
#define RB_BST_HPP

#include <numeric>
#include <iostream>
#include <cassert>
#include <vector>
#include <optional>
#include "storage.hpp"


/////// ---------------------- insert - cormen -------------
template<class V, class K=int, template<typename...> class CONT = std::vector>
struct rb_bst {

    using id_type = id_ui1f_type;
    template<class T>
    using container_type = CONT<T>;

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


    id_type root;
    storage_type<node, container_type, id_type> storage;

    // TODO: fancy constructors
    //rb_bst() { }

    node& operator[] (id_type const& id) {
        return storage[id];
    }

    node const& operator[] (id_type const& id) const {
        return storage[id];
    }

    bool is_RED(id_type id) const {
        if (id.is_NIL()) return false;
        return  storage[id].is_red();
    }

    void set_root(id_type x) {
        // root always has NIL parent and black
        storage[x].parent.set_NIL();
        //storage[x].parent = {}; // save color
        root = x;
    }

    id_type find_key(K const& k) const noexcept {
        id_type x = root;
        while (!x.is_NIL()) {
            if (k == storage[x].key) break;
            x = (k < storage[x].key) ? storage[x].left : storage[x].right;
        }
        return x;
    }

    std::optional<V> get_value(K const& k) const {
        if (auto const id = find_key(k); !id.is_NIL())
            return storage[id].val;
        return {};
    }

    V& operator[] (K const& k) {
        auto const id = find_key(k);
        if (id.is_NIL())
            throw int();
        return storage[id].val;
    }

    ///V operator[] (K const& k) const { // consider
    V const& operator[] (K const& k) const {
        auto const id = find_key(k);
        if (id.is_NIL())
            throw int();
        return storage[id].val;
    }

    auto node_min(id_type x) const {
        if (!x.is_NIL()) {
            while (!storage[x].left.is_NIL()) {
                x = storage[x].left;
            }
        }

        return x;
    }

    auto min() const {
        auto const id = node_min(root);
        if (id.is_NIL())
            throw int();

        struct {
            K key;
            V value;
        } const ret = { storage[id].key, storage[id].val };

        return ret;
    }

    auto node_max(id_type x) const {
        if (!x.is_NIL()) {
            while (!storage[x].right.is_NIL()) {
                x = storage[x].right;
            }
        }
        return x;
    }

    auto max() const {
        auto const id = node_max(root);
        if (id.is_NIL())
            throw int();

        struct {
            K key;
            V value;
        } const ret = { storage[id].key, storage[id].val };

        return ret;
    }


    void insert(K const& k, V const& v) {
        auto  id = storage.alloc();
        storage[id] = node{k, v};

        std::cerr << "insert " << id << ' ' << storage[id] << '\n';

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
        auto const z = find_key(k);
        if (z.is_NIL()) {
            return; // already 
        }

        std::cerr << "key (" << k << ") " << z << " is_red " << is_RED(z) << '\n';

        auto y = z;
        auto y_red = is_RED(y);
        id_type x;

        if (storage[z].left.is_NIL()) {
            std::cerr << "left null get right\n";
            x = storage[z].right;
            transplant(z, storage[z].right);
        } else if (storage[z].right.is_NIL()) {
            std::cerr << "right null get left\n";
            x = storage[z].left;
            transplant(z, storage[z].left);
        } else {
            y = node_min(storage[z].right);
            y_red = is_RED(y);
            std::cerr << "found next " << y <<  ' ' << "red " << y_red << std::endl;
            x = storage[y].right;
            std::cerr << "x " << x <<  ' ' << "red " << is_RED(y) << std::endl;
            if (storage[y].parent == z) {
                if (!x.is_NIL())
                    storage[x].parent = y;
            } else {
                transplant(y, storage[y].right);
                storage[y].right = storage[z].right;
                storage[storage[y].right].parent = y;
            }
            transplant(z, y);
            storage[y].left = storage[z].left;
            storage[storage[y].left].parent = y;
            storage[y].copy_color(storage[z]);
        }

        if (!y_red)
            erase_fix(x);

        std::cerr << "erased " << z << ' ' << storage[z] << '\n';
        storage.free(z);
    }


    void erase_fix(id_type x) {
        std::cerr << "erase_fix " << x << ' ' << is_RED(x) << '\n';
        if (x.is_NIL())
            return;
        
        while (x != root and !is_RED(x)) {
            auto& x_node = storage[x];
            if (storage[x_node.parent].left == x) {
                auto w = storage[x_node.parent].right;
                if (is_RED(w)) {
                    storage[w].set_black();
                    storage[x_node.parent].set_red();
                    left_rotate(x_node.parent);
                    w = storage[x_node.parent].right;
                }
                if (!is_RED(storage[w].left) && !is_RED(storage[w].right)) {
                    storage[w].set_red();
                    x = x_node.parent;
                }
                else {
                    if (!is_RED(storage[w].right)) {
                        storage[storage[w].left].set_black();
                        storage[w].set_red();
                        right_rotate(w);
                        w = storage[storage[w].parent].right;
                    }
                    storage[w].copy_color(storage[x].parent);
                    storage[storage[x].parent].set_black();
                    storage[storage[w].right].set_black();
                    left_rotate(storage[x].parent);
                    set_root(x);
                }
            }
            else {
                //TODO:...
            }
        }

        storage[x].set_black();
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
        std::cerr << "transplant " << u << " " << v << std::endl;
        auto& u_node = storage[u];
        if (u_node.parent.is_NIL()) {
            set_root(v);
        } else {
            auto& u_parent = storage[u_node.parent];
            (u == u_parent.left ? u_parent.left : u_parent.right) = v;
        }
        if (!v.is_NIL())
            storage[v].parent = u_node.parent;
    }


//---------------------------------------------------------

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
