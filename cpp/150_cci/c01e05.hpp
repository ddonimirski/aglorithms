#if !defined AL_150_CCI_C01_E05
#define AL_150_CCI_C01_E05

#include <string>

namespace a150_cci::c01::e05
{
    std::string replace_space(std::string& s) {

        auto cs = 0u;
        auto s_len = s.size();

        for (auto const v: s) cs += (v == ' ');

        auto const n_len = s_len + 2 * cs;
        if (s_len == n_len) return s;

        s.resize(n_len, '\0');
        for (int i = n_len-1 ; i >= 0; ) {
            if (s[--s_len] == ' ') {
                s[i--] = '0';
                s[i--] = '2';
                s[i--] = '%';
                continue;
            }
            s[i--] = s[s_len];
        }

        return s;
    }
} // namespace a150_cci::c01::e05
#endif // AL_150_CCI_C01_E05

