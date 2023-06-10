#ifndef JJ_ADDRESS_H_
#define JJ_ADDRESS_H_

#include <string>
#include <stdexcept>
#include <ostream>

namespace jj {

    [[nodiscard]] auto checked(std::string const& address) -> std::string;

    [[nodiscard]] auto is_correct(std::string const& address) -> bool;

    class Address {

        std::string address_;


        public:

        Address(std::string && address): address_{checked(std::move(address))} {}
        Address(std::string const& address): Address(std::string{address}) {}
        Address(char const* address): Address(std::string{address}) {}
        Address() = delete;
        Address(Address const&) = default;
        Address(Address &&) = default;
        Address& operator = (Address const&) = default;
        Address& operator = (Address &&) = default;
        ~Address() = default;

        friend inline auto operator == (Address const& a1, Address const& a2) -> bool {
            return a1.address_ == a2.address_;
        }

        friend inline auto to_str(Address const& addr) -> std::string {
            return addr.address_;
        }

        friend inline auto operator << (std::ostream& os, Address const& addr) -> std::ostream& {
            return os << to_str(addr);
        }

    };

} // namespace jj


template<>
struct std::hash<jj::Address>
{
    std::hash<std::string> hash_;

    auto operator()(jj::Address const& addr) const noexcept -> std::size_t {
        return hash_(to_str(addr));
    }
};


#endif // JJ_ADDRESS_H_
