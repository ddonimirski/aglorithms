#include <iostream>
using std::cerr, std::cout, std::endl;

struct ListNode {
    int val;
    ListNode* next = nullptr;

    ListNode(int v=0): val(v) {
        cerr << "val " << v << endl;
    }
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

    if (!l1) return l2;
    if (!l2) return l1;

    ListNode* ret = nullptr;
    int carry = 0;

    while(l1 && l2) {
        auto const v = l1->val + l2->val + carry;
        carry = v / 10;
        ListNode* val = new ListNode(v%10);
        val->next = ret;
        ret = val;

        l1 = l1->next;
        l2 = l2->next;
    }

    while (l1) {
        auto const v = l1->val + carry;
        carry = v / 10;
        ret->next = new ListNode(v%10);
        l1 = l1->next;
    }

    while (l2) {
        auto const v = l2->val + carry;
        carry = v / 10;         
        ret->next = new ListNode(v%10);
        l2 = l2->next;
    }

    if (carry) {
        ret->next = new ListNode(carry);
    }

    auto* head = red->next;

    return ret;
}
                                                                                
void pr(ListNode const* head) {
    while(head) {
        cerr << head->val << " -> ";
        head = head->next;
    }
    cerr << '\n';
}

void del(ListNode* h) {
    while (h) {
        auto* p = h;
        h =h->next;
        delete p;
    }
} 

int main() {
    ListNode l1[3];
    auto const l1_size = sizeof(l1)/sizeof(*l1);
    int i = 0;
    for (auto v: {2, 4, 3})
        l1[i++].val = v;

    ListNode l2[3];
    auto const l2_size = sizeof(l2)/sizeof(*l2);
    i = 0;
    for (auto v: {5, 6, 4})
        l2[i++].val = v;

    l1[0].next = &l1[1];
    l1[1].next = &l1[2];

    l2[0].next = &l2[1];
    l2[1].next = &l2[2];

    pr(l1);
    pr(l2);

    auto* p = addTwoNumbers(l1, l2);

    pr(p);
    del(p);
}
