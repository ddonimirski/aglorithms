#include <iostream>
#include <vector>
#include <cassert>

using std::cout, std::cerr , std::endl;
using std::vector;

using value_type = unsigned;


// runtime O(3^n), space O(n)
value_type triple_step_rec(value_type steps) {
    if (steps < 0) return 0;
    if (steps == 0) return 1;

    value_type sum = 0;
    if (steps >= 1) 
        sum += triple_step_rec(steps - 1);
    if (steps >= 2) 
        sum += triple_step_rec(steps - 2);
    if (steps >= 3)
        sum += triple_step_rec(steps - 3);

    return sum;
}

// run time O(n), space O(n)
value_type triple_step_rec(value_type steps, vector<value_type>& mem) {
    if (steps < 0) return 0;
    if (steps == 0) return 1;

    if (mem.size() <= steps) {
        value_type sum = 0;
        if (steps >= 1) 
            sum += triple_step_rec(steps - 1, mem);
        if (steps >= 2) 
            sum += triple_step_rec(steps - 2, mem);
        if (steps >= 3)
            sum += triple_step_rec(steps - 3, mem);

        if (mem.size() == steps)
            mem.push_back(sum);
        else {
            assert(false);
            //mem[steps] = sum;
        }
    }
#if defined PRINT_MEM
    else {
        cerr << "get from mem\n";
    }
#endif

    return mem[steps];
}


// run time O(n), space O(n)
value_type triple_step_int(value_type steps) {
    if (steps == 0) return 0;
    vector<value_type> mem(steps);
    mem[0] = 1;
    mem[1] = 2;
    mem[2] = 4;

    if (steps > 3) {
        for (value_type i = 3; i < steps; ++i) {
            mem[i] = mem[i-1] + mem[i-2] + mem[i-3];
        }
    }
    return mem[steps-1];
}


// run time O(n), space O(1)
value_type triple_step_int2(value_type steps) {

    if (steps == 0) return 0;

    value_type mem[] = {1, 2, 4};

    if (steps <= 3) return mem[steps-1];

    for (value_type i = 3; i < steps; ++i) {
        mem[i%3] = mem[0] + mem[1] + mem[2];
    }
    return mem[(steps-1)%3];
}

template<class T>
void pr(vector<T> const& c) {
    for (auto v: c)
        cout << v << ' ';
    cout << '\n';
}


value_type triple_step(value_type steps) {

    vector<value_type> mem = {0, 1};

    auto const sum = triple_step_rec(steps, mem);
    assert(sum == triple_step_int(steps));
    assert(sum == triple_step_int2(steps));
    return sum;
}


int main() {

    cout << triple_step(2) << endl;
    cout << triple_step(3) << endl;
    cout << triple_step(4) << endl;
    cout << triple_step(5) << endl;
    cout << triple_step(6) << endl;
    cout << triple_step(7) << endl;
    cout << triple_step(8) << endl;
    cout << triple_step(9) << endl;
    cout << triple_step(10) << endl;
}
