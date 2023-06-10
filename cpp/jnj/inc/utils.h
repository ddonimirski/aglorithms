#ifndef JJ_UTILS_H_
#define JJ_UTILS_H_

#include <sstream>
#include <string>

namespace jj {

    // function get a C array size
    template<class T, int N>
    constexpr inline auto size(T (&)[N]) -> int {
        return N;
    }

    // function make a XOR operation on text
    static inline auto cypher_text(std::string const& text, int value) -> std::string {
        std::string cypher = text;
        std::transform(cypher.cbegin(),
                        cypher.cend(),
                        cypher.begin(),
                        [value](auto item) { return item^value; });
        return cypher;
    }


    // function return string of any type that has std::ostream& operator <<(std::ostream&, ...)
    template<class ...Args>
    auto to_str(Args&& ...args) -> std::string {
        std::stringstream ss;
        (ss << ... << args);
        return ss.str();
    }

    // type decuction for variants (!won't work with std::visit)
    template<class ...Ts>
    struct overloaded: Ts... { using Ts::operator()...; };

    template<class ...Ts>
    overloaded(Ts ...) -> overloaded<Ts...>;

} // namespace jj

#endif // JJ_UTILS_H_
