#include <iostream>
#include <regex>

#include "logger/printfstream.h"
#include "logger/logger.h"
#include "logger/consolesink.h"
#include "logger/filesink.h"


struct Y {};



int main()
{
    int x = 0;
    StreamPrintf(std::cout, "a: %d\nb: %c\nc: %n (other stuff)\nd: %s\ne: %s\nf: %d\n", x, 65, &x, true, std::string("string"), 'y');
    StreamPrintf(std::cout, "|%3$-10.*2$f|", 15, 3, 1.234567);
    std::cout << std::endl << "x: " << x << std::endl;

    ConsoleSink consoleSink;
    //consoleSink.SetLevel(LOG_LEVEL_INFO);
    Logger::Instance().AddSink(consoleSink);
    FileSink fileSink("test.log");
    Logger::Instance().AddSink(fileSink);

    LOG_VERBOSE("verbose");
    LOG_DEBUG("debug");
    LOG_INFO("info");
    LOG_WARNING("warning");
    LOG_ERROR("error");

    return 0;
}

