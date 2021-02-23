#if !defined PR_HPP
#define PR_HPP
#include <iostream>
#include <array>
#include <string>

namespace print {

template<class T>
struct carr
{
    T const* arr;
    const size_t n;

    template<int N>
    carr(T (&a)[N]):arr(a), n(N) {}

    carr(T *a, size_t N): arr(a), n(N) {}

    friend std::ostream& operator << (std::ostream& os, carr const& in)
    {
        os << '[' << ' ';
        for (size_t i = 0; i < in.n; ++i)
            os << in.arr[i] << ' ' ;
        return os << ']';
    }
};


template <class CONT>
static void pr_cont(std::ostream& os, CONT&& cont)
{
    os << '[' << ' ';
    for (auto const& v: cont)
        os << v << ' ';
    os << ']';
} 


template<class T, template<typename...> class CONT>
    std::ostream& operator << (std::ostream& os, CONT<T>&& arr)
    {
        pr_cont(os, arr);
        return os; 
    }

template<class T, int N, template<typename, int> class CONT>
    std::ostream& operator << (std::ostream& os, CONT<T, N> const& arr)
    {
        pr_cont(os, arr);
        return os; 
    }

template<class T, int N>
    std::ostream& operator << (std::ostream& os, std::array<T, N> const& arr)
    {
        pr_cont(os, arr);
        return os; 
    }


template<class T, int N>
    std::ostream& operator << (std::ostream& os, T const(&arr)[N])
    {
        pr_cont(os, arr);
        return os; 
    }


template<class T>
struct sep
{
    const T _sep;
    sep(T&& s=" "): _sep{s} {}
    friend std::ostream& operator << (std::ostream& os, sep const& s)
    {
        return os << s._sep;
    }
};


struct to_str
{
    const char* _str;
    to_str(bool v): _str{v?"true":"false"} {}
    friend std::ostream& operator << (std::ostream& os, to_str const& s)
    {
        return os << s._str;
    }
};

template<class ...T>
static void pr(T ...args)
{
    using namespace print;
    ((std::cout << args << ' '), ...) << std::endl;
}

template<class ...T>
static void pr(std::ostream& os, T ...args)
{
    using namespace print;
    ((os << args << ' '), ...) << std::endl;
}


template<class S, class ...T>
static void pr(sep<S>&& sep, T ...args)
{
    ((std::cout << args << sep), ...) << std::endl;
}

template<class S, class ...T>
static void pr(std::ostream& os, sep<S>&& sep, T ...args)
{
    ((os << args << sep), ...) << std::endl;
}


#if defined LOG
template<class ...T>
static void log(T... args)
{
    pr("log", args...);
}
#else
#define log(...)
#endif

}

#endif //PR_HPP
