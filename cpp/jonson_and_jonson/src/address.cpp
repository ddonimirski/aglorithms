#include <address.h>
#include <regex>
#include <log.h>

namespace jj {

    namespace {
        std::regex const email_pattern{ R"([_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,4}))" };
    }

    [[nodiscard]] auto is_correct([[maybe_unused]] std::string const& address) -> bool {
        return regex_match(address, email_pattern);
    }

    [[nodiscard]] auto checked(std::string const& address) -> std::string {

        if (!is_correct(address)) {
            // add address;
            LOG_ERR("wrong address ", address);
            throw std::runtime_error("wrong address");
        }

        return address;
    }

} // namespace jj
