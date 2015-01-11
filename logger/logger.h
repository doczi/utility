#ifndef LOGGER_H
#define LOGGER_H

#include "printfstream.h"

#include <ctime>
#include <mutex>
#include <sstream>
#include <string>



enum LogLevel {
    LOG_LEVEL_VERBOSE,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_NONE
};



class LogSink
{
public:
    LogSink(): level(LOG_LEVEL_VERBOSE) {}
    virtual ~LogSink() = default;
    virtual void Log(
            LogLevel level,
            const char* file,
            int line,
            const std::string& message) = 0;
    LogLevel Level() const { return level; }
    void SetLevel(LogLevel value) { level = value; }
private:
    LogLevel level;
};



/**
 * Formats log messages and directs them to LogSinks. LOG macros call the Log
 * method on the objected returned by the Instance method. This class is thread
 * safe.
 */
class Logger
{
public:
    static std::string FormatHeader(
            LogLevel level,
            const char* file,
            int line);
    static Logger& Instance();
    void AddSink(LogSink& sink);
    void RemoveSink(const LogSink& sink);
    template<typename... Args> void Log(
            LogLevel level,
            const char *file,
            int line,
            const char *format,
            Args... args);
private:
    std::mutex mutex;
    std::vector<LogSink*> sinks;
};



#ifndef COMPILE_LOG_LEVEL
    #define COMPILE_LOG_LEVEL 0
#endif



/**
 * @def LOG(format, ...)
 *
 * Logs a message to the various LogSinks via Logger. Expects the same arument
 * list as printf.
 * @param format format string. See documentation of printf.
 * @param ... arguments. See documentation of printf.
 */

/**
 * @def LOG_VERBOSE
 * @see LOG
 */
#if (COMPILE_LOG_LEVEL <= 0)
    #define LOG_VERBOSE(...) Logger::Instance().Log( \
        LOG_LEVEL_VERBOSE, __FILE__, __LINE__, __VA_ARGS__)
#else
    #define LOG_VERBOSE(...)
#endif

/**
 * @def LOG_DEBUG
 * @see LOG
 */
#if (COMPILE_LOG_LEVEL <= 1)
    #define LOG_DEBUG(...) Logger::Instance().Log( \
        LOG_LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#else
    #define LOG_DEBUG(...)
#endif

/**
 * @def LOG_INFO
 * @see LOG
 */
#if (COMPILE_LOG_LEVEL <= 2)
    #define LOG_INFO(...) Logger::Instance().Log( \
        LOG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#else
    #define LOG_INFO(...)
#endif

/**
 * @def LOG_WARNING
 * @see LOG
 */
#if (COMPILE_LOG_LEVEL <= 3)
    #define LOG_WARNING(...) Logger::Instance().Log( \
        LOG_LEVEL_WARNING, __FILE__, __LINE__, __VA_ARGS__)
#else
    #define LOG_WARNING(...)
#endif

/**
 * @def LOG_ERROR
 * @see LOG
 */
#if (COMPILE_LOG_LEVEL <= 4)
    #define LOG_ERROR(...) Logger::Instance().Log( \
        LOG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#else
    #define LOG_ERROR(...)
#endif



/**
 * @param level log severity.
 * @param file source file the logging is initiated from.
 * @param line source line number the logging is initiated from.
 * @returns a formatted log header containing all parameters and a timestamp.
 */
inline std::string Logger::FormatHeader(
        LogLevel level,
        const char* file,
        int line)
{
    time_t rawtime;
    char timeBuffer[32];
    time(&rawtime);
    strftime(timeBuffer, sizeof(timeBuffer), "%F %T", localtime(&rawtime));

    std::ostringstream header;
    StreamPrintf(header, "%s [%c] %s:%05d", timeBuffer, "VDIWE "[level],
            file, line);

    std::string result = header.str();
    result.resize(60, ' ');
    result[result.size() - 1] = ' ';
    return result;
}



/**
 * @returns the global Logger used by the LOG macros.
 */
inline Logger& Logger::Instance() {
    static Logger instance;
    return instance;
}



/**
 * Adds sink to Logger so that it receives log messages after the call.
 * @param sink receives log messages.
 * @note sink must not be destroyed until it is removed from Logger.
 */
inline void Logger::AddSink(LogSink& sink) {
    std::lock_guard<std::mutex> lock(mutex);
    sinks.push_back(&sink);
}



/**
 * Removes sink from Logger so that it does not receive log messages anymore.
 * @param sink the sink to remove.
 */
inline void Logger::RemoveSink(const LogSink& sink) {
    std::lock_guard<std::mutex> lock(mutex);
    sinks.erase(std::find(sinks.begin(), sinks.end(), &sink));
}



template<typename... Args>
void Logger::Log(
        LogLevel level,
        const char *file,
        int line,
        const char *format,
        Args... args)
{
    std::ostringstream message;
    bool isMessageFormatted = false;
    std::lock_guard<std::mutex> lock(mutex);
    for (LogSink* sink: sinks) {
        if (level >= sink->Level()) {
            if (!isMessageFormatted) {
                StreamPrintf(message, format, args...);
                isMessageFormatted = true;
            }
            sink->Log(level, file, line, message.str());
        }
    }
}



#endif // LOGGER_H
