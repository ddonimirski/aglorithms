#if !defined TEST_HPP
#define TEST_HPP
#include <cassert>
#include <functional>
#include "gtest/gtest.h"

template<class CONT, class CMP=std::less<>>
bool is_sorted(CONT const& cont, CMP cmp = CMP())
{
    for (auto i = cont.size() - 1; i > 0 ; --i)
    {
        if (!cmp(cont[i-1], cont[i]))
        {
            return false;
        }
    }
    return true;
}


template<class T, int N, class CMP=std::less<>>
bool is_sorted(T (&cont)[N], CMP cmp = CMP())
{
    for (auto i = N - 1; i > 0 ; --i)
    {
        if (!cmp(cont[i-1], cont[i]))
        {
            return false;
        }
    }
    return true;
}

template<class CONT, class CMP=std::less<>>
bool is_sorted(CONT const& cont, size_t s, size_t e, CMP cmp = CMP())
{
    assert(s <= e);
    if (s == e) return true;
    
    for (auto i = s+1; i != e+1; ++i)
    {
        if (!cmp(cont[i-1], cont[i]))
        {
            return false;
        }
    }
    return true;
}

#define EXPECT_ITERABLE_BASE(PRED, expected, target) \
    do { \
        auto const& expected_ = expected; \
        auto const& target_ = target; \
        auto iter_expected_ = std::begin(expected_); \
        auto iter_target_ = std::begin(target_); \
        auto const eiter_expected_ = std::end(expected_); \
        auto const eiter_target_ = std::end(target_); \
        unsigned int i = 0; \
        while (iter_target_ != eiter_target_) { \
            if (iter_expected_ == eiter_expected_) {  \
                ADD_FAILURE() << #expected " has samller length then " #target; \
            } \
            PRED(*iter_expected_, *iter_target_) \
                << "Container " #expected " and " #target " differ at index " << i; \
            ++iter_expected_, ++iter_target_, ++i; \
        } \
        EXPECT_EQ(iter_expected_, eiter_expected_) << " has smaller length then ";\
    } while (false)

#define EXPECT_ITERABLE_EQ(expected, target) \
    EXPECT_ITERABLE_BASE(EXPECT_EQ, expected, target)


#endif //TEST_HPP
