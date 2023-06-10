#ifndef JJ_LOGGER_H
#define JJ_LOGGER_H
#include <string>
#include <log_msg.h>
#include <log_level.h>

namespace jj::log {

    struct Logger
    {
        static void write_to_log(LogMsg && msg);
    };

} // namespace jj::log
  //
#endif
