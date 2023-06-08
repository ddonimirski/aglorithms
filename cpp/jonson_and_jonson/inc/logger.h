#ifndef JJ_LOGGER_H
#define JJ_LOGGER_H
#include <string>
#include <log_msg.h>
#include <log_level.h>

namespace jj::log {


    class Logger
    {
        public:
        static auto level() -> LogLevel;
        static auto filename() -> std::string const&;

        static void level(LogLevel level);
        static void filename(std::string const& filename);
        static void write_to_log(LogMsg && msg);

#if defined TEST_ACCESSORS
        // TODO
#endif
    };

} // namespace jj::log
  //
#endif
