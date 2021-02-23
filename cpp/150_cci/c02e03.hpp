#if !defined AP_150_CCI_C02_E03
#define AP_150_CCI_C02_E03

#include <iostream>


namespace a150_cci::c02::c03
{

struct node_list {
    int data;
    node_list* next = nullptr;
    node_list(int i = 0):data(i) {}
};


void pr(node_list* head) {

    while(head) {
        std::cout << head->data << ' ';
        head = head->next;
    }
    std::cout << '\n';
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

} // namespace a150_cci::c02::c03

#if 0
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
#endif

#endif // AP_150_CCI_C02_E03
