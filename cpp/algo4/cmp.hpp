#if !defined CMP_HPP
#define CMP_HPP

struct less
{
    template<class T>
    static bool compare(T const& v1, T const& v2)
    {
        return v1 < v2;
    }
};

#endif //CMP_HPP
