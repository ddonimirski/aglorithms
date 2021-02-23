#if !defined AL_150_CCI_C01_E02
#define AL_150_CCI_C01_E02

#include <algorithm>

namespace a150_cci::c01::e02
{

        void revers(char* str, std::size_t len) {

#if NO_STL
            auto swap = [](auto l, auto r) noexcept {
                auto const t = l;
                l = r;
                r = t;

            };

            for (auto l = 0lu, r = len-1; l<r; ) {
                swap(str[l++], str[r--]);
            }
#else
            for (auto l = 0lu, r = len-1; l < r;)
            {
                std::swap(str[l++], str[r--]);
            }
#endif
        }

} // namespace a150_cci::c01

#endif // AL_150_CCI_C01_E02
