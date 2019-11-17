#if !defined STACK_HPP
#define STACK_HPP
#include <utility>
#include <array>
#include <vector>
#include <optional>
#include "pr.hpp"

template<class T, int N=20>
struct carray_policy
{
    using cont_t = T[N];

    static void push_back(cont_t& cont, size_t& size, T&& v)
    {
        if (size < N)
        {
            cont[size++] = std::forward<T>(v);
        }
    }

    static T pop_back(cont_t& cont, size_t& size)
    {
        return cont[--size];
    }

    static T top_back(cont_t const& cont, size_t size)
    {
        return cont[size-1];
    }
};

template<class T, int N=20>
struct array_policy
{
    using cont_t=std::array<T, N>;

    static void push_back(cont_t& cont, size_t& size, T&& v)
    {
        if (size < N)
        {
            cont[size++] = std::forward<T>(v);
        }
    }

    static T pop_back(cont_t& cont, size_t& size)
    {
        return cont[--size];
    }

    static T top_back(cont_t const& cont, size_t size)
    {
        return cont[size-1];
    }
};


template<class T>
struct vector_policy
{
    using cont_t=std::vector<T>;

    static void push_back(cont_t& cont, size_t& size, T&& v)
    {
        if (size < cont.size())
        {
            cont[size++] = std::forward<T>(v);
        }
        else
        {
           cont.push_back(std::forward<T>(v));
           size = cont.size();
        }
    }

    static T pop_back(cont_t& cont, size_t& size)
    {
        return cont[--size];
    }

    static T top_back(cont_t const& cont, size_t size)
    {
        return cont[size-1];
    }
};

template<class T>
struct nodes_list_policy
{
    struct node
    {
        T _value;
        node *_next = nullptr;

        explicit node (T&& v): _value(std::forward<T>(v)) {}
        node (T&& v, node* n): _value(std::forward<T>(v)), _next(n) {}
    };
    using cont_t = node*;

    static void push_back(cont_t& cont, size_t& size, T&& v)
    {
        cont = new node(std::forward<T>(v), size == 0 ? nullptr : cont);
        ++size;
    }

    static T pop_back(cont_t& cont, size_t& size)
    {
        T ret = cont->_value;
        cont = cont->_next;
        --size;
        return ret;
    }

    static T top_back(cont_t const& cont, size_t)
    {
        return cont->_value;
    }
};

template<class T, class P = array_policy<T>>
struct stack
{
    using value_t = T;
    typename P::cont_t _cont;
    size_t _size=0;

    bool empty() const { return _size == 0; }
    auto size() const { return _size; }

    void push(value_t&& v)
    {
        P::push_back(_cont, _size, std::forward<T>(v));
    }

    std::optional<value_t> top() const
    {
        return empty()?std::optional<T>():P::top_back(_cont, _size);
    }

    std::optional<value_t> pop()
    {
        return empty()?std::optional<T>():P::pop_back(_cont, _size);
    }
};

#endif //STACK_HPP

