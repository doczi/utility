#ifndef FILESINK_H
#define FILESINK_H

#include "logger.h"

#include <fstream>



class FileSink: public LogSink
{
public:
    FileSink(const std::string& path):
        logFile(path, std::fstream::out | std::fstream::app)
    {}

    void Log(
            LogLevel level,
            const char* file,
            int line,
            const std::string& message) override
    {
        logFile << Logger::FormatHeader(level, file, line) << message <<
                std::endl;
    }
private:
    std::fstream logFile;
};



#endif // FILESINK_H
