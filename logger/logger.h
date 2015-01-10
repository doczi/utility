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
    static std::string FormatHeader(
            LogLevel level,
            const char* file,
            int line)
    {
        time_t rawtime;
        char timeBuffer[32];
        time(&rawtime);
        strftime(timeBuffer, sizeof(timeBuffer), "%F %T", localtime(&rawtime));

        std::ostringstream header;
        StreamPrintf(header, "%s [%c] %s:%05d", timeBuffer, "VDIWE"[level],
                file, line);

        std::string result = header.str();
        result.resize(60, ' ');
        result[result.size() - 1] = ' ';
        return result;
    }

    LogSink():
        level(LOG_LEVEL_VERBOSE)
    {}

    virtual ~LogSink() = default;

    virtual void Log(
            LogLevel level,
            const char* file,
            int line,
            const std::string& message) = 0;

    LogLevel Level() const {
        return level;
    }

    void SetLevel(LogLevel value) {
        level = value;
    }
private:
    LogLevel level;
};



class Logger
{
public:
    static Logger& Instance() {
        static Logger instance;
        return instance;
    }

    void AddSink(LogSink& sink) {
        std::lock_guard<std::mutex> lock(mutex);
        sinks.push_back(&sink);
    }

    void RemoveSink(const LogSink& sink) {
        std::lock_guard<std::mutex> lock(mutex);
        sinks.erase(std::find(sinks.begin(), sinks.end(), &sink));
    }

    template<typename... Args>
    void Log(
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
 * Writes a line of text to stdout on desktop, logcat on android. Uses the same
 * syntax as printf.
 * @param format format string. See documentation of printf.
 * @param ... arguments. See documentation of printf.
 */
#if (COMPILE_LOG_LEVEL <= 0)
    #define LOG_VERBOSE(...) Logger::Instance().Log( \
        LOG_LEVEL_VERBOSE, __FILE__, __LINE__, __VA_ARGS__)
#else
    #define LOG_VERBOSE(...)
#endif

#if (COMPILE_LOG_LEVEL <= 1)
    #define LOG_DEBUG(...) Logger::Instance().Log( \
        LOG_LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#else
    #define LOG_DEBUG(...)
#endif

#if (COMPILE_LOG_LEVEL <= 2)
    #define LOG_INFO(...) Logger::Instance().Log( \
        LOG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#else
    #define LOG_INFO(...)
#endif

#if (COMPILE_LOG_LEVEL <= 3)
    #define LOG_WARNING(...) Logger::Instance().Log( \
        LOG_LEVEL_WARNING, __FILE__, __LINE__, __VA_ARGS__)
#else
    #define LOG_WARNING(...)
#endif

#if (COMPILE_LOG_LEVEL <= 4)
    #define LOG_ERROR(...) Logger::Instance().Log( \
        LOG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#else
    #define LOG_ERROR(...)
#endif



#endif // LOGGER_H
