#ifndef JJ_LOG_LEVEL_H
#define JJ_LOG_LEVEL_H

#include <string>

namespace jj::log {

        enum class LogLevel: int {
            SEC = 0,
            ERR,
            WAR,
            MSG,
            DBG,
        };

        inline auto to_log_level(std::string const& ll) -> LogLevel {
            if (ll == "DBG") { return LogLevel::DBG; }
            if (ll == "MSG") { return LogLevel::MSG; }
            if (ll == "WAR") { return LogLevel::WAR; }
            if (ll == "ERR") { return LogLevel::ERR; }
            if (ll == "SEC") { return LogLevel::SEC; }

            return LogLevel::SEC;
        }

        inline auto to_str_level(LogLevel level) -> std::string {
            switch(level) {
                case LogLevel::DBG: return "DBG";
                case LogLevel::MSG: return "MSG";
                case LogLevel::WAR: return "WAR";
                case LogLevel::ERR: return "ERR";
                case LogLevel::SEC: return "SEC";
            }

            // should not heppen
            return "NOP";
        }
} // namespace jj::log

#endif 
