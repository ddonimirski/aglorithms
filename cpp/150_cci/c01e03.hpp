#if !defined AL_150_CCI_C01_E03
#define AL_150_CCI_C01_E03


#include <cstdint>
#include <string>
#include <algorithm>


namespace a150_cci::c01::e03
{
    int remove_duplicates(char* s, std::size_t len) {

        auto tail = 1u;
        for (auto i = 1u, j = 0u; i < len; ++i) {
            for (j = 0; j < tail; ++j) {
                if (s[i] == s[j]) {
                    break;
                }
            }
            if (j == tail) {
                s[tail++] = s[i];
            }
        }

        s[tail] = 0;
        return tail;
    }


    int remove_duplicates(std::string& s) {

        auto tail = 1u;
        auto len = s.size();
        for (auto i = 1u, j = 0u; i < len; ++i) {
            for (j = 0; j < tail; ++j) {
                if (s[i] == s[j]) {
                    break;
                }
            }
            if (j == tail) {
                s[tail++] = s[i];
            }
        }

        s.resize(tail);
        return tail;
    }


} // namespace 150_cci::c01

#endif // AL_150_CCI_C01_E03
