#ifndef PRINTFSTREAM_H
#define PRINTFSTREAM_H

#include "printfparser.h"

#include <ostream>
#include <sstream>
#include <stdexcept>



struct GetInt
{
    template<typename T>
    typename std::enable_if<std::is_integral<T>::value, int>::type
    operator()(T argument) const { return argument; }

    template<typename T>
    typename std::enable_if<!std::is_integral<T>::value, int>::type
    operator()(const T&) const {
        throw std::logic_error("Expected integer value.");
    }
};



struct Print
{
    std::ostream* stream;
    PrintfParser parser;
    int count;

    void operator()(char argument) {
        if ((parser.Specifier() == 'c') || (parser.Specifier() == 's')) {
            PrintArgument(argument);
        } else {
            PrintArgument(static_cast<int>(argument));
        }
    }

    void operator()(wchar_t argument) {
        if ((parser.Specifier() == 'c') || (parser.Specifier() == 's')) {
            PrintArgument(argument);
        } else {
            PrintArgument(static_cast<int>(argument));
        }
    }

    template<typename T>
    typename std::enable_if<std::is_arithmetic<T>::value>::type
    operator()(T argument) {
        if (parser.Specifier() == 'c') {
            if (parser.Length() == sizeof(long)) {
                PrintArgument(static_cast<wchar_t>(argument));
            } else {
                PrintArgument(static_cast<char>(argument));
            }
        } else {
            PrintArgument(argument);
        }
    }

    template<typename T>
    typename std::enable_if<std::is_integral<T>::value>::type
    operator()(T* argument) {
        if (parser.Specifier() == 'n') {
            *argument = count;
        } else {
            PrintArgument(argument);
        }
    }

    template<typename T>
    typename std::enable_if<std::is_integral<T>::value>::type
    operator()(const T* argument) { PrintArgument(argument); }

    template<typename T>
    typename std::enable_if<!std::is_arithmetic<T>::value>::type
    operator()(const T& argument) { PrintArgument(argument); }

    template<typename T>
    void PrintArgument(const T& argument) {
        std::ostringstream oss;
        if (parser.Width() != PrintfParser::UNSPECIFIED) {
            oss.width(parser.Width());
        }
        if (parser.Precision() != PrintfParser::UNSPECIFIED) {
            oss.precision(parser.Precision());
        }
        if (parser.Fill() != PrintfParser::UNSPECIFIED) {
            oss.fill(parser.Fill());
        }
        oss.flags(parser.FormatFlags());
        oss << argument;
        count += oss.str().size();
        *stream << oss.str();
    }
};



template<typename F, typename T, typename... Args>
auto ProcessNth(F&& function, int i, const T& argument, Args... args) ->
    decltype(function(argument))
{
    return (i == 0) ? function(argument) : ProcessNth(function, i - 1, args...);
}



template<typename F>
auto ProcessNth(F&& function, int) -> decltype(function(0))
{
    throw std::logic_error("Not enough arguments");
}



template<typename... Args>
int StreamPrintf(std::ostream& stream, const char* format, Args... args)
{
    Print print;
    print.count = 0;
    print.stream = &stream;

    int arg = 0;
    size_t i = 0;
    while (format[i] != '\0') {
        if (format[i] != '%') {
            ++i;
            continue;
        }
        stream.write(format, i);
        format += i;
        print.count += i;
        i = 0;
        if (format[1] == '%') {
            stream.write("%", 1);
            format += 2;
        } else {
            format = print.parser.ParseFormat(format);
            if (print.parser.ValueIndex() == PrintfParser::UNSPECIFIED) {
                print.parser.SetValueIndex(arg++);
            }
            if (print.parser.Width() == PrintfParser::WILDCARD) {
                if (print.parser.WidthIndex() == PrintfParser::UNSPECIFIED) {
                    print.parser.SetWidth(ProcessNth(GetInt(), arg++, args...));
                } else {
                    print.parser.SetWidth(ProcessNth(GetInt(), print.parser.WidthIndex(), args...));
                }
            }
            if (print.parser.Precision() == PrintfParser::WILDCARD) {
                if (print.parser.PrecisionIndex() == PrintfParser::UNSPECIFIED) {
                    print.parser.SetPrecision(ProcessNth(GetInt(), arg++, args...));
                } else {
                    print.parser.SetPrecision(ProcessNth(GetInt(), print.parser.PrecisionIndex(), args...));
                }
            }
            ProcessNth(print, print.parser.ValueIndex(), args...);
        }
    }
    stream.write(format, i);
    print.count += i;
    return print.count;
}



#endif // PRINTFSTREAM_H
