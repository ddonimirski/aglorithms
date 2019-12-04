#if !defined TEST_HPP
#define TEST_HPP

template<class CONT, class CMP=::less>
bool is_sorted(CONT const& cont)
{
    for (auto i = cont.size() - 1; i > 0 ; --i)
    {
        if (CMP::compare(cont[i-1], cont[i]))
        {
            return false;
        }
    }
    return true;
}

#endif //TEST_HPP
