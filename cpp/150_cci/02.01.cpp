#include <iostream>
#include <cassert>
#include <vector>


using std::cout, std::cerr , std::endl;
using std::cin;
using std::vector;


struct node_list {
    int data;
    node_list* next = nullptr;
    node_list(int i = 0):data(i) {}
};

constexpr int MAX_RANGE = 50;

//std::vector<node_list> mem(100);

node_list* remove_duplicates(node_list* head) {
    vector<int> count(MAX_RANGE); // if range is large should be hashtable
    if (head == nullptr) {
        return head;
    }

    count[head->data]++;

    node_list* del_head = nullptr;
    node_list* del_tail = nullptr;

    while (head && head->next) {
        if (count[head->next->data]) {
            if (del_head == nullptr) {
                del_head = del_tail = head->next;
            } 
            else {
                del_tail->next = head->next;
                del_tail = del_tail->next;
            }
            head->next = head->next->next;
            del_tail->next = nullptr;
        }
        else {
            count[head->next->data]++;
            head = head->next;
        }
    }

    return del_head;
}

node_list* remove_duplicates_noaddstorage(node_list* head) {
    auto* const head_ancor = head;

    auto find = [begin = head_ancor] (auto* end, int data) mutable  {
        while (begin != end && begin->data != data)
            begin = begin->next;
        return begin != end;
    };

    node_list* del_head = nullptr;
    node_list* del_tail = nullptr;

    while (head && head->next) {

        if (find(head->next, head->next->data)) {
            if (del_head == nullptr) {
                del_head = del_tail = head->next;
            }
            else {
                del_tail->next = head->next;
                del_tail = del_tail->next;
            }
            head->next = head->next->next;
            del_tail->next = nullptr;
        }
        else {
            head = head->next;
        }
    }

    return  del_head;
}

void pr(node_list* head) {

    while(head) {
        cout << head->data << ' ';
        head = head->next;
    }
    cout << '\n';
}


void del_list(node_list* head) {
    while(head) {
        auto* tmp = head;
        head = head->next;
        delete tmp;
    }
}

int main() {

    int N;
    cin >> N;

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
    //if (auto* del = remove_duplicates(head)) del_list(del);
    if (auto* del = remove_duplicates_noaddstorage(head)) del_list(del);
    pr(head);


}
