#if !defined COST_FUNCTION
#define COST_FUNCTION

#include <chrono>
#include <random>
#include <memory>

namespace utils
{
    template<size_t N, unsigned SEED = 0>
    auto costFun(size_t i, size_t j) // prepare cost matrix
    {
        static auto init = [&]()
        {
            static_assert(N>0, "diment N must be greater then 0");

            struct matrix
            {
                size_t const n_;
                size_t const size_;
                std::unique_ptr<int[]> data_;

                matrix():
                    n_(N),
                    size_(N*N),
                    data_(std::make_unique<int[]>(size_))
                {
                    constexpr auto seed = (SEED != 0) ? SEED : std::chrono::system_clock::now().time_since_epoch().count();
                    std::default_random_engine gen(seed);
                    std::uniform_int_distribution<> dist(1, 1000);
                    auto beg = data_.get();
                    auto const end = beg + size_;

                    while(beg != end)
                    {
                        *beg++ = -1;
                    }
                    for (auto i = 0ul; i < n_; ++i)
                    {
                        (*this)[i][i] = 0;
                        for (auto j = i+1; j < n_; ++j)
                        {
                            (*this)[i][j] = dist(gen);
                        }
                    }
                }

                int* operator[](int row_id)
                {
                    return data_.get() + row_id * n_;
                }

            } mx;

        #if 0
            /// --
            for (int i = 0; i < mx.n_; ++i)
            {
                std::cerr << '[';
                for (int j = 0; j < mx.n_; ++j)
                {
                    std::cerr << mx[i][j] << ' ';
                }
                std::cerr << ']' << '\n';
            }
            /// ---
         #endif

            return mx;
        };

            static auto arr = init();
            return arr[i][j];
        }

}

#endif // COST_FUNCTION
