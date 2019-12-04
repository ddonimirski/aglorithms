#if !defined PR_HPP
#define PR_HPP
#include <iostream>
#include <array>

template <class CONT>
static void pr_cont(std::ostream& os, CONT&& cont)
{
    os << '[' << ' ';
    for (auto const& v: cont)
        os << v << ' ';
    os << ']';
} 

template<class T, template<typename> class CONT>
std::ostream& operator << (std::ostream& os, CONT<T> const& arr)
{
    pr_cont(os, arr);
    return os; 
}

template<class T, auto N>
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


template<class ...T>
static void pr(T ...args)
{
    ((std::cout << args << ' ' ), ...) << std::endl;
}

template<class T>
struct sep_t
{
    const T _sep;
    sep_t(T&& s): _sep{s} {}
    friend std::ostream& operator << (std::ostream& os, sep_t const& sep)
    {
        return os << sep._sep;
    }
};

template<class S, class ...T>
static void pr(sep_t<S>&& sep, T ...args)
{
    ((std::cout << args << sep), ...) << std::endl;
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


#endif //PR_HPP
