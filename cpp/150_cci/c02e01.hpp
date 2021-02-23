#if !defined AP_150_CCI_C02_E01
#define  AP_150_CCI_C02_E01

#include <iostream>
#include <vector>


namespace a150_cci::c02::e01
{

struct node_list {
    int data;
    node_list* next = nullptr;
    node_list(int i = 0):data(i) {}
};

constexpr int MAX_RANGE = 50;


node_list* remove_duplicates(node_list* head) {

    std::vector<int> count(MAX_RANGE); // if range is large should be hashtable

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
        std::cout << head->data << ' ';
        head = head->next;
    }
    std::cout << '\n';
}


void del_list(node_list* head) {
    while(head) {
        auto* tmp = head;
        head = head->next;
        delete tmp;
    }
}

} // namespace a150_cci::c02::e01


#endif // AP_150_CCI_C02_E01
