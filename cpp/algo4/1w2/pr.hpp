#if !defined PR_HPP
#define PR_HPP
#include <iostream>

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
