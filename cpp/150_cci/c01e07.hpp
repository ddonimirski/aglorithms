#if !defined AP_150_CCI_C01_E07
#define AP_150_CCI_C01_E07

#include <vector>
#include <utils/matrix.hpp>


namespace a150_cci::c01::e07
{

template<class T>
void set_zero(utils::matrix<T>& m) {

    std::vector<bool> row(m.__row_size);
    std::vector<bool> col(m.__col_size);

    for (size_t r = 0; r < m.__row_size; ++r)
        for (size_t c = 0; c < m.__col_size; ++c)
            if (m[r][c] == 0)
                col[c] = row[r] = 1;


    for (size_t r = 0; r < m.__row_size; ++r)
        for (size_t c = 0; c < m.__col_size; ++c)
            if (col[c] || row[r])
                m[r][c] = 0;
}

} // namespace a150_cci::c01::e07


#endif // AP_150_CCI_C01_E07
