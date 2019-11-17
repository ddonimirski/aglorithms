#include "stack.hpp"
#include <cassert>

int main()
{
    { // default_policy
        stack<int> st;
        assert(st.empty());
        assert(st.size()==0);
        assert(!st.top());
        st.push(10);
        assert(st.top() && st.top() == 10);
        assert(st.size()==1);
        st.push(20);
        assert(st.top() && st.top() == 20);
        assert(st.size()==2);
        auto v = st.pop();
        assert(v && v == 20);
        assert(st.size()==1);
        v = st.pop();
        assert(v && v == 10);
        assert(st.size()==0);
        assert(st.empty());
        v = st.pop();
        assert(!v);
    }

    { // carray_policy
        stack<int, carray_policy<int,10>> st;
        assert(st.empty());
        assert(st.size()==0);
        assert(!st.top());
        st.push(10);
        assert(st.top() && st.top() == 10);
        assert(st.size()==1);
        st.push(20);
        assert(st.top() && st.top() == 20);
        assert(st.size()==2);
        auto v = st.pop();
        assert(v && v == 20);
        assert(st.size()==1);
        v = st.pop();
        assert(v && v == 10);
        assert(st.size()==0);
        assert(st.empty());
        v = st.pop();
        assert(!v);
    }

    { // array_policy
        stack<int, array_policy<int,10>> st;
        assert(st.empty());
        assert(st.size()==0);
        assert(!st.top());
        st.push(10);
        assert(st.top() && st.top() == 10);
        assert(st.size()==1);
        st.push(20);
        assert(st.top() && st.top() == 20);
        assert(st.size()==2);
        auto v = st.pop();
        assert(v && v == 20);
        assert(st.size()==1);
        v = st.pop();
        assert(v && v == 10);
        assert(st.size()==0);
        assert(st.empty());
        v = st.pop();
        assert(!v);
    }

    { // vector_poilicy
        stack<int, vector_policy<int>> st;
        assert(st.empty());
        assert(st.size()==0);
        assert(!st.top());
        st.push(10);
        assert(st.top() && st.top() == 10);
        assert(st.size()==1);
        st.push(20);
        assert(st.top() && st.top() == 20);
        assert(st.size()==2);
        auto v = st.pop();
        assert(v && v == 20);
        assert(st.size()==1);
        v = st.pop();
        assert(v && v == 10);
        assert(st.size()==0);
        assert(st.empty());
        v = st.pop();
        assert(!v);
    }
    { // nodes_list_policy
        stack<int, nodes_list_policy<int>> st;
        assert(st.empty());
        assert(st.size()==0);
        assert(!st.top());
        st.push(10);
        assert(st.top() && st.top() == 10);
        assert(st.size()==1);
        st.push(20);
        assert(st.top() && st.top() == 20);
        assert(st.size()==2);
        auto v = st.pop();
        assert(v && v == 20);
        assert(st.size()==1);
        v = st.pop();
        assert(v && v == 10);
        assert(st.size()==0);
        assert(st.empty());
        v = st.pop();
        assert(!v);
    }
}
