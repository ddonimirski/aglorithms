#if !defined TEST_HPP
#define TEST_HPP
#include <cassert>

template<class CONT, class CMP=::less>
bool is_sorted(CONT const& cont)
{
    for (auto i = cont.size() - 1; i > 0 ; --i)
    {
        if (!CMP::compare(cont[i-1], cont[i]))
        {
            return false;
        }
    }
    return true;
}


template<class T, int N, class CMP=::less>
bool is_sorted(T (&cont)[N])
{
    for (auto i = N - 1; i > 0 ; --i)
    {
        if (!CMP::compare(cont[i-1], cont[i]))
        {
            return false;
        }
    }
    return true;
}

template<class CONT, class CMP=::less>
bool is_sorted(CONT const& cont, size_t s, size_t e)
{
    assert(s <= e);
    if (s == e) return true;
    
    for (auto i = s+1; i != e+1; ++i)
    {
        if (!CMP::compare(cont[i-1], cont[i]))
        {
            return false;
        }
    }
    return true;
}


#endif //TEST_HPP
