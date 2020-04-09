#include <iostream>
#include <cassert>

using std::cout, std::cerr , std::endl;
using std::cin;


struct node_list {
    int data;
    node_list* next = nullptr;
    node_list(int i = 0):data(i) {}
};


void pr(node_list* head) {

    while(head) {
        cout << head->data << ' ';
        head = head->next;
    }
    cout << '\n';
}


bool delete_node(node_list* node) {

    if (node == nullptr || node->next == nullptr) {
        return false;
    }

    auto* next = node->next;
    node->data = next->data;
    node->next = next->next;
    delete next;

    return true;
}


int main() {

    int N, n;
    cin >> n >> N;

    if (n > N) { cerr << ":)" << endl; return 0; }

    node_list* head = nullptr;
    node_list* tail = nullptr;

    while (N--) {
        int val;
        cin >> val;
        auto* v = new node_list(val);

        if (head == nullptr) {
            head = tail = v;
        }
        else {
            tail->next = v;
            tail = tail->next;
        }
    }

    pr(head);

    auto* ptr = head;
    for (int i = 1; i < n; ++i) {
       ptr = ptr->next; 
    }
    if (!delete_node(ptr)) {
        cerr << "no delete :{" << endl;
    }

    pr(head);
}
