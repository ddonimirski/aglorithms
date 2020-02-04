#if !defined AVL_TREE_HPP 
#define AVL_TREE_HPP 

template <class T>
struct avl_tree {

    struct node {
        T key;
        node* left;
        node* right;
        unsigned size;
    };
};

#endif // AVL_TREE_HPP 
