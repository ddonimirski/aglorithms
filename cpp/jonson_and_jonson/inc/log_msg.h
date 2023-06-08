#ifndef JJ_LOG_MSG_H
#define JJ_LOG_MSG_H

#include <string>
#include <log_level.h>

namespace jj::log {

    struct LogMsg {
        LogLevel level_;
        std::string file_;
        std::string func_;
        int line_;
        std::string msg_;
    };

    void to_log_line(std::ostream& os, LogMsg const& msg) ;

} // namespace jj::log {
  //
#endif // JJ_LOG_MSG_H
