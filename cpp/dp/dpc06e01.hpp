#if !defined DP_CH06_E01_H
#define DP_CH06_E01_H

namespace dp::ch06::e01
{
    auto fib(int n)
    {
        if (n==1 || n==2) return 1ull;

        auto a = 1ull;
        auto b = 1ull;
        auto c = 1ull;

        for (int i = 0; i < n; ++i)
        {
            c = a + b;
            a = b;
            b = c;
        }

        return c;
    }
} // namespace dp::ch06::e01

#endif // DP_CH06_E01_H
