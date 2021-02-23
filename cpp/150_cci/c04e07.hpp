#if !defined AP_150_CCI_C04_E07
#define AP_150_CCI_C04_E07

#include <iostream>

namespace a150_cci::c04::e07
{

//BST

template<class T>
struct node  {
    node* left = nullptr;
    node* right = nullptr;
    T value;
};

using node_type = node<int>;

bool match_tree(node_type const* t1, node_type const* t2) {
    if (t1 == nullptr && t2 == nullptr) return true;
    if (t1 == nullptr || t2 == nullptr) return false;

    std::cerr << t1->value << ' ' << t2->value << '\n';
    if (t1->value != t2->value) { std::cerr << "mt <> \n"; return false; }
    return match_tree(t1->left, t2->left) && match_tree(t1->right, t2->right);
}

bool sub_tree(node_type const* t1, node_type const* t2) {
    //if (t1 == nullptr) return false; // t2 was checked before :P
    if (t1 == nullptr && t2 == nullptr) { std::cerr << "st nn \n"; return true; }
    if (t1 == nullptr || t2 == nullptr)  { std::cerr << "st n|n \n"; return false; }
    if (t1->value == t2->value) return match_tree(t1, t2);
    return sub_tree(t1->left, t2) || sub_tree(t1->right, t2);
}

bool contains_tree(node_type const* t1, node_type const* t2) {
    if (t2 == nullptr) return true;
    return sub_tree(t1, t2);
}

} // namespace a150_cci::c04::e07


#endif // AP_150_CCI_C04_E07
