#include <iostream>
#include <vector>
#include <cassert>

using std::cout, std::cerr, std::endl;

// in_order traversal


struct node {
    int data;
    node* left = nullptr;
    node* right = nullptr;

    node(int d): data{d} {}
};

void in_order(node* r) {
    if (r == nullptr) return;

    if (r->left) in_order(r->left);
    cout << r->data << ' ';
    if (r->right) in_order(r->right);
}

int main() {

    node* root = new node{4};
    root->left = new node{2};
    root->left->left = new node{1};
    root->left->right = new node{3};
    root->right = new node{6};
    root->right->left = new node{5};
    root->right->right = new node{7};

    in_order(root);
    cout << endl;
}
