#if !defined PR_HPP
#define PR_HPP
#include <iostream>
#include <array>


template <class CONT>
static void pr_contener(CONT&& cont, size_t s, size_t e)
{
    std::cout << '(' << s << ':' << e <<')' << '[' << ' ';
    for (; s <= e; ++s) {
        std::cout  << cont[s] << ' ';
    }
    std::cout << ']' << std::endl;
} 

template <class CONT>
static void pr_cont(std::ostream& os, CONT&& cont)
{
    os << '[' << ' ';
    for (auto const& v: cont)
        os << v << ' ';
    os << ']';
} 


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

template<class T, template<typename> class CONT>
std::ostream& operator << (std::ostream& os, CONT<T> const& arr)
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
