#if !defined STACK_HPP
#define STACK_HPP
#include <utility>
#include <array>
#include <vector>
#include <optional>


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
        return empty()?std::optional<T>():_cont[_size-1];
    }

    std::optional<value_t> pop()
    {
        return empty()?std::optional<T>():_cont[--_size];
    }

};

#endif //STACK_HPP

