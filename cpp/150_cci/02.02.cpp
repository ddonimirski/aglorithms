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

void pr(node_list* head) {

    while(head) {
        cout << head->data << ' ';
        head = head->next;
    }
    cout << '\n';
}

int remove_nth (node_list* head, int n) {
    if (head && n > 0) {
        n = remove_nth(head->next, n) - 1;    
         if (n == -1) {
             if (auto* tmp = head->next->next; tmp != nullptr) {
                 head->next->data = tmp->data;
                 head->next->next = tmp->next;
                 delete tmp;
             }
         }
    }
    return n;
}

#if 0
node_list* remove_nth_norec(node_list* head, int n) {
    // not work
    std::vector<node_list*> mem;

    while (head) {
        mem.push_back(head);
        head = head->next;
    }

    if (n < 0 || n > mem.size()) return head;

    auto const tmp_id = mem.size()-n;
    cerr << "tmp_id " << tmp_id << ' ' << mem[tmp_id]->data <<  endl;

    if (tmp_id == 0) {
        delete mem[tmp_id];
        return mem.size() == 1 ? nullptr : mem[tmp_id+1];
    }

     if (tmp_id + 1 == mem.size()) {
         cerr << "last one " << mem[tmp_id-1]->data << endl;
         mem[tmp_id-1]->next = nullptr;
     }
     else {
         mem[tmp_id-1]->next = mem[tmp_id+1];
     }

     delete mem[tmp_id];

    return head;
}
#endif


node_list* remove_nth_norec(node_list* head, int n) {

    if (!head) return head;

    node_list* p1 = head, *p2 = head;

    while(n--) {
        p2 = p2->next;
        if (!p2) {
            head = head->next;
            delete p1;
            return head;
        }
    }

    while(p2->next) {
        p1 = p1->next;
        p2 = p2->next;
    }

    auto* tmp = p1->next;

    if (tmp) {
        if (tmp->next) {
            p1->next = p1->next->next;
        }
        else {
            p1->next = nullptr;
        }
        delete tmp;
    }

    return head;
}


node_list* last_n(node_list* head, int n) {

    if (head == nullptr || n < 1) return nullptr;

    auto* p1 = head;
    auto* p2 = head;


    for (int i = 0; i < n-1; ++i) {
        if (p2 == nullptr) return p2;
        p2 = p2->next;
    }

    while (p2->next) {
        p1 = p1->next;
        p2 = p2->next;
    }

    return p1;
}


int main() {

    int N, n;
    cin >> n;
    cin >> N;

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
    //?? remove_nth(head, n);
    //head = remove_nth_norec (head, n);
    //
    pr(last_n(head, n));

    pr(head);
}