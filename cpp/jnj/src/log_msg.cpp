#include <log_msg.h>
#include <ostream>
#include <string_view>

namespace jj::log {

    void to_log_line(std::ostream& os, LogMsg const& msg) {

        auto cut_filename = [](std::string_view file) -> std::string_view {
            return file.substr(file.rfind('/'));
        };
    
        os << to_str_level(msg.level_) << '|'
           << cut_filename(msg.file_) << ':'
           << msg.func_ << ':'
           << msg.line_ << '|'
           << msg.msg_;
    }

} // namespace jj::log {
