#include <iostream>
#include <cassert>
#include <vector>

using std::cout, std::cerr , std::endl;
using std::cin;
using std::vector;


struct 3stacks {

    struct node {
        int id;
        int data;
    };

    constexpr int capacity = 300;
    constexpr int num_stacks = 3;

    vector<node> storage(capacity);
    vector<int> stack_id(num_stacks); // posiibly change dynamicly
    vector<int> stack_size(num_stacs); // posiibly change dynamicly
    int left = capacity;

    int free = 0;

    3stacks() {
        auto curr = 1;
        for (auto& v: storage) v = curr++;
    }

    bool is_empty(
};

int main() {
}
