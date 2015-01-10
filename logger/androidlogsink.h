#ifndef ANDROIDLOGSINK_H
#define ANDROIDLOGSINK_H

#include "logger.h"

#include <android/log.h>



class ConsoleSink: public LogSink
{
public:
    void Log(
            LogLevel level,
            const char* file,
            int,
            const std::string& message) override
    {
        static const android_LogPriority ANDROID_LOG_PRIORITIES[] = {
            ANDROID_LOG_VERBOSE,
            ANDROID_LOG_DEBUG,
            ANDROID_LOG_INFO,
            ANDROID_LOG_WARN,
            ANDROID_LOG_ERROR
        };
        __android_log_print(ANDROID_LOG_PRIORITIES[level], file, "%s",
                message.c_str());
    }
};



#endif // ANDROIDLOGSINK_H
