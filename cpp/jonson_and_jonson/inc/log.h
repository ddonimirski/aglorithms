#ifndef JJ_LOG_H
#define JJ_LOG_H

#include <log_msg.h>
#include <logger.h>
#include <utils.h>

template<class ... Args>
auto log_msg(
        jj::log::LogLevel level,
        std::string const& file,
        std::string const& func,
        int line,
        Args&& ...args) -> jj::log::LogMsg {

    return  { 
        .level_ = level,
        .file_ = file,
        .func_  = func,
        .line_ = line,
        .msg_ = jj::to_str(args...)
    };

}
// TODO  pritty funtion name name/ short file path
#define LOG_BASE(level, ...) ::jj::log::Logger::write_to_log(jj::log::LogMsg{ .level_ = level, .file_ = __FILE__, .func_ = (char const*)__PRETTY_FUNCTION__, .line_ = __LINE__, .msg_ = jj::to_str(__VA_ARGS__)});
// #define LOG_BASE(level, ...) ::jj::log::Logger::write_to_log(log_msg(level, __FILE__,__PRETTY_FUNCTION__,__LINE__, __VA_ARGS__));
#define LOG_DBG(...) LOG_BASE(jj::log::LogLevel::DBG, __VA_ARGS__);
#define LOG_MSG(...) LOG_BASE(jj::log::LogLevel::MSG, __VA_ARGS__);
#define LOG_WAR(...) LOG_BASE(jj::log::LogLevel::WAR, __VA_ARGS__);
#define LOG_ERR(...) LOG_BASE(jj::log::LogLevel::ERR, __VA_ARGS__);
#define LOG_SEC(...) LOG_BASE(jj::log::LogLevel::SEC, __VA_ARGS__);

#endif
