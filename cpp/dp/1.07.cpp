#include <iostream>
#include <vector>
#include <cassert>

using std::cout, std::cerr, std::endl;

// head i tail recursion

struct node {
    int data;
    node* next = nullptr;

    node(int d): data{d} {}
};

void traversa1(node* head) {
    if (head != nullptr) {
        traversa1(head->next);
        cout << head->data << ' ';
    }
}

void traversa2(node* head) {
    if (head != nullptr) {
        cout << head->data << ' ';
        traversa2(head->next);
    }
}


int main() {

    auto* head = new node{0};
    for (int i = 1; i < 10; ++i) {
        auto* tmp = new node(i);
        tmp->next = head;
        head = tmp;
    }

    cout << " traversa1: ";
    traversa1(head);
    cout << endl;

    cout << " traversa2: ";
    traversa2(head);
    cout << endl;
}
