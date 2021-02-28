#if !defined DP_CH01_E07
#define DP_CH01_E07

#include <iostream>
#include <memory>

// head i tail recursion
//
namespace dp::ch01::e07
{

struct node {
    int data;
    std::shared_ptr<node> next;

    node(int d): data{d} {}
};

void traversa1(std::ostream& os, std::shared_ptr<node>& head) {
    if (head) {
        traversa1(os, head->next);
        os << head->data << '\n';
    }
}

void traversa2(std::ostream& os, std::shared_ptr<node>& head) {
    if (head) {
        os << head->data << '\n';
        traversa2(os, head->next);
    }
}

} // namespace dp::ch01::e07


#endif // DP_CH01_E07
