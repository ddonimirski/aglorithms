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
