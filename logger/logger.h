#ifndef LOGGER_H
#define LOGGER_H

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "formatter.h"



enum LogLevel {
    LOG_LEVEL_VERBOSE,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_NONE
};



#ifndef COMPILE_LOG_LEVEL
    #define COMPILE_LOG_LEVEL LOG_LEVEL_VERBOSE
#endif



class Logger
{
public:
    Logger();
    static Logger& getInstance();

    template<typename... Args>
    void log(
            LogLevel level,
            const char *file,
            int line,
            const char *format,
            Args... args);

    void setConsoleLogLevel(LogLevel level);
    void setFileLogLevel(LogLevel level);
    void setLogPath(const std::string &path);
private:
    std::ofstream mLogFile;
    LogLevel mConsoleLogLevel;
    LogLevel mFileLogLevel;
};



/**
 * @def LOG(format, ...)
 *
 * Writes a line of text to stdout on desktop, logcat on android. Uses the same
 * syntax as printf.
 * @param format format string. See documentation of printf.
 * @param ... arguments. See documentation of printf.
 */
#if (COMPILE_LOG_LEVEL <= LOG_LEVEL_VERBOSE)
    #define LOG_VERBOSE(...) Logger::getInstance().log( \
        LOG_LEVEL_VERBOSE, __FILE__, __LINE__, __VA_ARGS__)
#else
    #define LOG_VERBOSE(...)
#endif

#if (COMPILE_LOG_LEVEL <= LOG_LEVEL_DEBUG)
    #define LOG_DEBUG(...) Logger::getInstance().log( \
        LOG_LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#else
    #define LOG_DEBUG(...)
#endif

#if (COMPILE_LOG_LEVEL <= LOG_LEVEL_INFO)
    #define LOG_INFO(...) Logger::getInstance().log( \
        LOG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#else
    #define LOG_INFO(...)
#endif

#if (COMPILE_LOG_LEVEL <= LOG_LEVEL_WARNING)
    #define LOG_WARNING(...) Logger::getInstance().log( \
        LOG_LEVEL_WARNING, __FILE__, __LINE__, __VA_ARGS__)
#else
    #define LOG_WARNING(...)
#endif

#if (COMPILE_LOG_LEVEL <= LOG_LEVEL_ERROR)
    #define LOG_ERROR(...) Logger::getInstance().log( \
        LOG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#else
    #define LOG_ERROR(...)
#endif



/* Implementation */

#ifdef PLATFORM_ANDROID

#include <android/log.h>

android_LogPriority ANDROID_LOG_PRIORITIES[] = {
    ANDROID_LOG_VERBOSE,
    ANDROID_LOG_DEBUG,
    ANDROID_LOG_INFO,
    ANDROID_LOG_WARN,
    ANDROID_LOG_ERROR
};

#endif // PLATFORM_ANDROID



inline Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
}



inline Logger::Logger():
    mConsoleLogLevel(LOG_LEVEL_DEBUG),
    mFileLogLevel(LOG_LEVEL_WARNING)
{}



/**
 * Writes a line of text to stdout on desktop, logcat on android. Use this only
 * via the LOG macro.
 * @param file name of the file the function is called from.
 * @param line of source code the function is called from.
 * @param format format string. See documentation of printf.
 * @param ... arguments. See documentation of printf.
 */
template<typename... Args>
void Logger::log(
        LogLevel level,
        const char* file,
        int line,
        const char* format,
        Args... args)
{
    if (level >= LOG_LEVEL_NONE) {
        return;
    }
    if ((level < mConsoleLogLevel) && (level < mFileLogLevel)) {
        return;
    }

    time_t rawtime;
    char timeBuffer[32];
    time(&rawtime);
    strftime(timeBuffer, sizeof(timeBuffer), "%F %T", localtime(&rawtime));

    std::ostringstream header;
    Formatter(header, "%s [%c] %s:%05d    ").write(
            timeBuffer, "VDIWE"[level], file, line);

    std::ostringstream message;
    Formatter(message, format).write(args...);

    if (level >= mFileLogLevel) {
        mLogFile << header.str() << message.str() << std::endl;
    }

    if (level >= mConsoleLogLevel) {
#ifndef PLATFORM_ANDROID
        std::clog << header.str() << message.str() << std::endl;
#else
        __android_log_print(ANDROID_LOG_PRIORITIES[level], file, "%s",
                message.str().c_str());
#endif
    }
}



inline void Logger::setConsoleLogLevel(LogLevel level)
{
    mConsoleLogLevel = level;
}



inline void Logger::setFileLogLevel(LogLevel level)
{
    mFileLogLevel = level;
}



inline void Logger::setLogPath(const std::string &path)
{
    mLogFile.open(path.c_str(), std::ios::out | std::ios::app);
}



#endif // LOGGER_H
