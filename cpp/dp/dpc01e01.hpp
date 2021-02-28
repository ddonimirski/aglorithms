#if !defined DP_CH01_E01
#define DP_CH01_E01

namespace dp::ch01::e01
{
//
// count recursive sum of contener
//

template<class T, template <typename...> class C, class I = int >
T sum(C<T> const& c, I i = 0)  {
    if (i == c.size()) return T{};
    return c[i] + sum(c, i+1);
}

} // namespace dp::ch01::e01


#endif // DP_CH01_E01
