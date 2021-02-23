#if !defined AP_150_CCI_C01_E08
#define AP_150_CCI_C01_E08

#include <string_view>

namespace a150_cci::c01::e08
{

bool is_rotate(std::string_view s1, std::string_view s2) {

    auto const size = s2.size();
    std::string s(2*size+1, 0);

    s2.copy(s.data(), size);
    s2.copy(s.data()+size, size);

    return std::string::npos != s.find(s1);
}
} // namespace a150_cci::c01::e08

#endif // AP_150_CCI_C01_E08
