#include <logger.h>
#include <log_msg.h>
#include <iostream>
#include <mutex>
#include <fstream>
#include <sstream>


#ifndef LOG_LEVEL
auto constexpr DEFAULT_LOG_LEVEL = "DBG";
#else
auto constexpr DEFAULT_LOG_LEVEL = #LOG_LEVEL;
#endif

#ifndef LOG_FILENAME
auto constexpr DEFAULT_LOG_FILENAME = "log.txt";
#else
auto constexpr DEFAULT_LOG_FILENAME = #LOG_FILENAME
#endif


namespace jj::log {

    namespace {
        // NOLINTBEGIN
        LogLevel current_log_level_ = to_log_level(DEFAULT_LOG_LEVEL);
        std::string log_filename_ = DEFAULT_LOG_FILENAME;
        std::mutex log_mtx_;
        // NOLINTEND
    }

    void Logger::write_to_log(LogMsg && msg) {

        if (static_cast<int>(msg.level_) <=  static_cast<int>(current_log_level_)) {

            std::lock_guard<std::mutex> lock(log_mtx_);

            std::stringstream ss;

            to_log_line(ss, msg);
            (void)std::move(msg);

            std::cerr << ss.str() << std::endl;

            static std::ofstream log_file(DEFAULT_LOG_FILENAME);
            log_file << ss.str() << std::endl;
        }
    }
}  // namespace jj::log
