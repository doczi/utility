#ifndef CONSOLESINK_H
#define CONSOLESINK_H

#include "logger.h"

#if defined(_WIN32)
    #include <io.h>
#else
    #include <unistd.h>
#endif


#include <iostream>



class ConsoleSink: public LogSink
{
public:
    void Log(
            LogLevel level,
            const char* file,
            int line,
            const std::string& message) override
    {
        if (IsTerminal()) {
            static const char* const COLORS[] = {
                "\x1b[37m",
                "\x1b[94m",
                "\x1b[32m",
                "\x1b[33m",
                "\033[31m"
            };
            std::clog << COLORS[level] <<
                    Logger::FormatHeader(level, file, line) << message <<
                    "\x1b[0m" << std::endl;
        } else {
            std::clog << Logger::FormatHeader(level, file, line) << message <<
                    std::endl;
        }
    }
private:
    bool IsTerminal() {
#if defined(_WIN32)
        return _isatty(STDERR_FILENO);
#else
        return isatty(STDERR_FILENO);
#endif
    }
};



#endif // CONSOLESINK_H
