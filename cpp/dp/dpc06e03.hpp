#if !defined DP_CH06_E03_H
#define DP_CH06_E03_H

#include <iostream>

// DP top - down

namespace dp::ch06::e03
{
    template<class FUN>
    auto minCost(size_t s, size_t d, FUN cost)
    {

#if PRINT_COST
        for (int i = s; i <= d; ++i)
        {
            std::cerr << '[';
            for (int j = s; j <= d; ++j)
            {
                std::cerr << cost(i, j) << ' ';
            }
            std::cerr << ']' << '\n';
        }
#endif // PRINT_COST

        struct array
        {
            using type_t = int;
            size_t n_;
            type_t* const data_;
            array(size_t n): n_(n), data_{new type_t[n]} { }

            ~array() { delete [] data_; }

            type_t& operator[](int i) { return data_[i]; }

        } min_cost(d+1);

        min_cost[s] = 0;
        min_cost[s+1] = cost(s,s+1);

        for (size_t i = s+2; i <= d; ++i)
        {
            min_cost[i] = cost(s, i);
            for (size_t j = s; j < i; ++j)
            {
                if (min_cost[i] > min_cost[j] + cost(j, i))
                {
                    min_cost[i] = min_cost[j] + cost(j, i);
                }
            }
        }

#if PRINT_MEMO
        std::cerr << "====================\n";
        for (int i = s; i <= d; ++i)
        {
            std::cerr << min_cost[i] << ' ';
        }
        std::cerr << '\n';
        std::cerr << "====================\n";
#endif // PRINT_MEMO

        return min_cost[d];
    }

} // namespace dp::ch06::e03

#endif // DP_CH06_E03_H
