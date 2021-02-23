#include "c02e01.hpp"
#include "c02e02.hpp"
#include "c02e03.hpp"

#include "gtest/gtest.h"

#include <utils/pr.hpp>

TEST(c02e01, node_list)
{
#if 0
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
#endif
}


TEST(c02e02, remove_nth)
{
#if 0
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
#endif
}
