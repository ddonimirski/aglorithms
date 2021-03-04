#if !defined SCOPE_TIMER_HPP
#define SCOPE_TIMER_HPP

#include <chrono>
#include <string_view>
#include <iostream>

namespace utils
{
    struct scope_timer final
    {
        using clock_type = std::chrono::steady_clock;
        explicit scope_timer(std::string_view name, std::ostream& os = std::cout):
            function_name_{name}, start_{clock_type::now()}, os_(os) { }

        scope_timer(scope_timer const&) = delete;
        scope_timer(scope_timer &&) = delete;
        auto operator =(scope_timer const&) -> scope_timer& = delete;
        auto operator =(scope_timer &&) -> scope_timer& = delete;

        ~scope_timer()
        {
            using namespace std::chrono;
            auto const stop = clock_type::now();
            auto const duration = (stop - start_);
            auto const ms = duration_cast<milliseconds>(duration).count();
            os_ << ms << " ms " << function_name_ << '\n';
        }

        private:
            std::string_view function_name_{};
            clock_type::time_point start_{};
            std::ostream& os_;
    };

    template<class FUN, class ...Args>
    static inline auto check_time(std::ostream&os, std::string_view name, FUN fun, Args... args)
    {
        scope_timer st(name, os);
        return fun(args...);
    }

#define CHECK_TIME(os, fun, ...) utils::check_time(os, #fun, fun, __VA_ARGS__)
}

#endif // SCOPE_TIMER_HPP

