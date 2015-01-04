#ifndef PRINTFSTREAM_H
#define PRINTFSTREAM_H

#include "printfparser.h"

#include <ostream>
#include <sstream>



class PrintfStream
{
public:
    PrintfStream(std::ostream& stream, const char* format);

    template<typename T, typename... Args>
    typename std::enable_if<std::is_integral<T>::value, int>::type
    Print(const T& argument, Args... args); // Integral

    template<typename T, typename... Args>
    typename std::enable_if<std::is_integral<T>::value, int>::type
    Print(T* argument, Args... args); // Output

    template<typename T, typename... Args>
    typename std::enable_if<std::is_integral<T>::value, int>::type
    Print(const T* argument, Args... args); // Generic

    template<typename T, typename... Args>
    typename std::enable_if<!std::is_integral<T>::value, int>::type
    Print(const T& argument, Args... args); // Generic

    int Print();
private:
    std::ostream& stream;
    const char* format;
    PrintfParser parser;
    int count;

    void PrintFormat();
    template<typename T> void PrintArgument(const T& argument);
};



PrintfStream::PrintfStream(std::ostream &stream, const char *format):
    stream(stream),
    format(format),
    count(0)
{
    PrintFormat();
}



template<typename T, typename... Args>
typename std::enable_if<std::is_integral<T>::value, int>::type
PrintfStream::Print(const T& argument, Args... args)
{
    if (parser.Width() == PrintfParser::WILDCARD) {
        parser.SetWidth(argument);
    } else if (parser.Precision() == PrintfParser::WILDCARD) {
        parser.SetPrecision(argument);
    } else if (parser.Specifier() == 'c') {
        if (parser.Length() == sizeof(long)) {
            PrintArgument(static_cast<wchar_t>(argument));
        } else {
            PrintArgument(static_cast<char>(argument));
        }
        PrintFormat();
    } else {
        PrintArgument(argument);
        PrintFormat();
    }
    Print(args...);
    return count;
}



template<typename T, typename... Args>
typename std::enable_if<std::is_integral<T>::value, int>::type
PrintfStream::Print(T* argument, Args... args)
{
    if (parser.Specifier() == 'n') {
        *argument = count;
    } else {
        PrintArgument(argument);
    }
    PrintFormat();
    Print(args...);
    return count;
}



template<typename T, typename... Args>
typename std::enable_if<std::is_integral<T>::value, int>::type
PrintfStream::Print(const T* argument, Args... args)
{
    PrintArgument(argument);
    PrintFormat();
    Print(args...);
    return count;
}



template<typename T, typename... Args>
typename std::enable_if<!std::is_integral<T>::value, int>::type
PrintfStream::Print(const T& argument, Args... args)
{
    PrintArgument(argument);
    PrintFormat();
    Print(args...);
    return count;
}



int PrintfStream::Print()
{
    stream << format;
    return count;
}



void PrintfStream::PrintFormat()
{
    size_t i = 0;
    while (format[i] != '\0') {
        if (format[i] == '%') {
            stream.write(format, i);
            format += i;
            i = 0;
            if (format[1] == '%') {
                 ++format;
            } else {
                format = parser.ParseFormat(format);
                return;
            }
        }
        ++i;
    }
}



template<typename T>
void PrintfStream::PrintArgument(const T& argument)
{
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
    stream << oss.str();
}



template<typename... Args>
int StreamPrintf(std::ostream& stream, const char* format, Args... args)
{
    return PrintfStream(stream, format).Print(args...);
}



#endif // PRINTFSTREAM_H
