#ifndef JJ_ADDRESS_H_
#define JJ_ADDRESS_H_

#include <string>
#include <stdexcept>

namespace jj {

class Address {

    std::string address_;

    static inline auto is_correct(std::string const& address) noexcept -> bool {
        return true;
    }

    static inline auto checked(std::string && address) -> std::string {

        if (!is_correct(address)) {
            // add address;
            throw std::runtime_error("wrong address");
        }

        return address;
    }


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

        auto operator == (Address const& a) const -> bool {
            return address_ == a.address_;
        }

        friend inline auto to_str(Address const& addr) -> std::string {
            return addr.address_;
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
