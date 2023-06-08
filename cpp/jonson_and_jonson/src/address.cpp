#include <address.h>

namespace jj {

    [[nodiscard]] auto is_correct([[maybe_unused]] std::string const& address) noexcept -> bool {
        // TODO implement
        return true;
    }

    [[nodiscard]] auto checked(std::string const& address) -> std::string {

        if (!is_correct(address)) {
            // add address;
            throw std::runtime_error("wrong address");
        }

        return address;
    }

} // namespace jj
