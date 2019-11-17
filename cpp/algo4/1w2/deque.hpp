#if !defined DEQUE_HPP
#define DEQUE_HPP
#include <optional>
#include <array>


template<class T, int N=20>
struct array_policy
{
    using cont_t = std::array<T,N>();

    void add_first(cont_t& cont, size_t& first,  size_t last, T&& v)
    {
        if (auto const id = (first == 0) ? N-1 : first-1; id != last)
        {
            cont[first - id] = std::forward<T>(v);
        }
        else
        {
            //throw full
        }
    }

    void add_last(cont_t& cont, size_t first,  size_t& last, T&& v)
    {
        if (auto const id = (last + 1) % N; id != first)
        {
            cont[last = id] = std::forward<T>(v);
        }
        else
        {
            //throw full
        }
    }

    T rm_first(cont_t& cont, size_t& first, size_t last)
    {
        T ret = cont[first];
        first = (++first) %N;

        return ret;
    }

    T rm_last(cont_t& cont, size_t first, size_t last)
    {
        T ret = cont[last];
        if (last == 0)
            last = N-1;

        return ret;
    }
}

template<class T, class P=array_policy<T,20>>
struct deque
{
    size_t _first = 0, _last = 0;
    typename P::cont_t _cont;

    bool empty() const { return _first == _last; }

    //size_t size() const { return _size; }

    void add_first(T&& v)
    {
        if (!P::full(_cont, _size))
        {
            P::add_first(_cont, _size, std::forward<T>());
        }
    }

    void add_last(T&& v)
    {
        if (!P::full(_cont, _size))
        {
            P::add_last(_cont, _size, std::forward<T>());
        }
    }

    std::optional<T> remove_first()
    {
        return empty()?std::optional<T>():P::remove_first(_cont, _size);
    }

    std::optional<T> remove_last()
    {
        return empty()?std::optional<T>():P::remove_last(_cont, _size);
    }
};

#endif //DEQUE_HPP
