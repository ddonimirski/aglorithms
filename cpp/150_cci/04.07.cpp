#include <iostream>
#include <cassert>
#include <vector>

using std::cout, std::cerr , std::endl;
using std::cin;
using std::vector;

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

    cerr << t1->value << ' ' << t2->value << endl;
    if (t1->value != t2->value) { cerr << "mt <> \n"; return false; }
    return match_tree(t1->left, t2->left) && match_tree(t1->right, t2->right);
}

bool sub_tree(node_type const* t1, node_type const* t2) {
    //if (t1 == nullptr) return false; // t2 was checked before :P
    if (t1 == nullptr && t2 == nullptr) { cerr << "st nn \n"; return true; }
    if (t1 == nullptr || t2 == nullptr)  { cerr << "st n|n \n"; return false; }
    if (t1->value == t2->value) return match_tree(t1, t2);
    return sub_tree(t1->left, t2) || sub_tree(t1->right, t2);
}

bool contains_tree(node_type const* t1, node_type const* t2) {
    if (t2 == nullptr) return true;
    return sub_tree(t1, t2);
}

node_type st[50];
node_type st2[50];
node_type st3[50];


int main() {

    st[0].value = 5;
    st[0].left = st+1;
    st[0].right = st+2;
    st[1].value = 3;
    st[1].left = st+3;
    st[1].right = st+4;
    st[2].value = 7;
    st[2].left = st+5;
    st[2].right = st+6;
    st[3].value = 1;
    st[3].left = nullptr; 
    st[3].right = nullptr;
    st[4].value = 4;
    st[4].left = nullptr;
    st[4].right = nullptr;
    st[5].value = 6;
    st[5].left = nullptr; 
    st[5].right = nullptr;
    st[6].value = 8;
    st[6].left = nullptr;
    st[6].right = nullptr;


    st2[0].value = 5;
    st2[0].left = st+1;
    st2[0].right = st+2;
    st2[1].value = 3;
    st2[1].left = st+3;
    st2[1].right = st+4;
    st2[2].value = 7;
    st2[2].left = st+5;
    st2[2].right = st+6;
    st2[3].value = 1;
    st2[3].left = nullptr; 
    st2[3].right = nullptr;
    st2[4].value = 4;
    st2[4].left = nullptr;
    st2[4].right = nullptr;
    st2[5].value = 6;
    st2[5].left = nullptr; 
    st2[5].right = nullptr;
    st2[6].value = 8;
    st2[6].left = nullptr;
    st2[6].right = nullptr;

    cout << "nono2: " <<  contains_tree(&st[0], &st2[0]) << endl;


    node<int> s;
    s.value = 5;

    cout << "nono1: " <<  contains_tree(st, &s) << endl;
}
