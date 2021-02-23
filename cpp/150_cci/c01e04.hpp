#if !defined AL_150_CCI_C01_E04
#define AL_150_CCI_C01_E04

#include <cctype>
#include <string_view>


namespace a150_cci::c01::e04
{

bool is_anagram(std::string_view s1, std::string_view s2) noexcept {

    int c['z'-'a'+1];
    constexpr auto c_len = sizeof(c)/sizeof(*c);

    for (auto& v: c) v = 0;

    for (auto const v: s1) ++c[std::tolower(v)-'a'];

    for (auto const v: s2) --c[std::tolower(v)-'a'];

    int s = 0;
    for (auto const v: c) s += std::abs(v);

    return !s;
}

} // namespace a150_cci::c01::e04

#endif // AL_150_CCI_C01_E04
