#ifndef PRINTFPARSER_H
#define PRINTFPARSER_H

#include <cassert>
#include <cinttypes>
#include <iostream>



class PrintfParser
{
public:
    static const int UNSPECIFIED = -1;
    static const int WILDCARD = -2;

    const char* ParseFormat(const char* format);
    std::ios_base::fmtflags FormatFlags() const { return formatFlags; }
    void SetFormatFlags(std::ios_base::fmtflags value) { formatFlags = value; }
    int ValueIndex() const { return valueIndex; }
    void SetValueIndex(int value) { valueIndex = value; }
    int Width() const { return width; }
    void SetWidth(int value) { width = value; }
    int WidthIndex() const { return widthIndex; }
    void SetWidthIndex(int value) { widthIndex = value; }
    int Precision() const { return precision; }
    void SetPrecision(int value) { precision = value; }
    int PrecisionIndex() const { return precisionIndex; }
    void SetPrecisionIndex(int value) { precisionIndex = value; }
    int Length() const { return length; }
    void SetLength(int value) { precision = value; }
    char Fill() const { return fill; }
    void SetFill(char value) { fill = value; }
    char Specifier() const { return specifier; }
    void SetSpecifier(char value) { specifier = value; }
private:
    std::ios_base::fmtflags formatFlags;
    int valueIndex;
    int width;
    int widthIndex;
    int precision;
    int precisionIndex;
    int length;
    char fill;
    char specifier;

    const char* ProcessPercent(const char* format);
    const char* ProcessAlignment(const char* format);
    const char* ProcessWidth(const char* format);
    const char* ProcessPrecision(const char* format);
    const char* ProcessLength(const char* format);
    const char* ProcessSpecifier(const char* format);
};



inline const char* PrintfParser::ParseFormat(const char* format)
{
    format = ProcessPercent(format);
    format = ProcessAlignment(format);
    format = ProcessWidth(format);
    format = ProcessPrecision(format);
    format = ProcessLength(format);
    format = ProcessSpecifier(format);
    return format;
}



inline const char* PrintfParser::ProcessPercent(const char* format)
{
    valueIndex = UNSPECIFIED;
    int number = 0;
    for (const char* i = format;; ++i) {
        switch (*i) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            number = 10 * number + (*i - '0');
            break;
        case '$':
            valueIndex = number - 1;
            return i + 1;
        case '%':
            if (i == format) {
                break;
            } else {
                return (valueIndex != UNSPECIFIED) ? i : (format + 1);
            }
        default:
            return (valueIndex != UNSPECIFIED) ? i : (format + 1);
        }
    }
    assert(false); // unreachable
    return nullptr;
}



inline const char* PrintfParser::ProcessAlignment(const char* format)
{
    fill = ' ';
    formatFlags &= ~(std::ios_base::adjustfield | std::ios_base::showpos |
            std::ios_base::showbase);
    formatFlags |= std::ios_base::right;
    for (const char* i = format;; ++i) {
        switch (*i) {
        case '-':
            formatFlags &= ~std::ios_base::right;
            formatFlags |= std::ios_base::left;
            break;
        case '+':
            formatFlags |= std::ios_base::showpos;
            break;
        case ' ':
            fill = ' ';
            break;
        case '#':
            formatFlags |= std::ios_base::showbase;
            break;
        case '0':
            fill = '0';
            break;
        default:
            return i;
        }
    }
    assert(false); // unreachable
    return nullptr;
}



inline const char* PrintfParser::ProcessWidth(const char* format)
{
    width = UNSPECIFIED;
    for (const char* i = format;; ++i) {
        switch (*i) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if (width < 0) {
                width = 0;
            }
            width = 10 * width + (*i - '0');
            break;
        case '*':
            width = WILDCARD;
            break;
        case '$':
            widthIndex = width - 1;
            width = WILDCARD;
            break;
        default:
            return i;
        }
    }
    assert(false); // unreachable
    return nullptr;
}



inline const char* PrintfParser::ProcessPrecision(const char* format)
{
    precision = UNSPECIFIED;
    for (const char* i = format;; ++i) {
        switch (*i) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if (precision < 0) {
                precision = 0;
            }
            precision = 10 * precision + (*i - '0');
            break;
        case '*':
            precision = WILDCARD;
            break;
        case '$':
            precisionIndex = precision - 1;
            precision = WILDCARD;
            break;
        case '.':
            break;
        default:
            return i;
        }
    }
    assert(false); // unreachable
    return nullptr;
}



inline const char* PrintfParser::ProcessLength(const char* format)
{
    length = UNSPECIFIED;
    for (const char* i = format;; ++i) {
        switch (*i) {
        case 'h':
            length = (length == UNSPECIFIED) ? sizeof(short) : sizeof(char);
            break;
        case 'l':
            length = (length == UNSPECIFIED) ? sizeof(long) : sizeof(long long);
            break;
        case 'j':
            length = sizeof(intmax_t);
            break;
        case 'z':
            length = sizeof(size_t);
            break;
        case 't':
            length = sizeof(ptrdiff_t);
            break;
        case 'L':
            length = sizeof(long double);
            break;
        default:
            return i;
        }
    }
    assert(false); // unreachable
    return nullptr;
}



inline const char* PrintfParser::ProcessSpecifier(const char* format)
{
    specifier = *format;
    formatFlags &= ~(std::ios_base::basefield | std::ios_base::floatfield |
            std::ios_base::uppercase | std::ios_base::boolalpha);

    switch (*format) {
    case 'd':
    case 'i':
    case 'u':
        formatFlags |= std::ios_base::dec;
        break;
    case 'o':
        formatFlags |= std::ios_base::oct;
        break;
    case 'x':
        formatFlags |= std::ios_base::hex;
        break;
    case 'X':
        formatFlags |= std::ios_base::hex | std::ios_base::uppercase;
        break;
    case 'f':
        formatFlags |= std::ios_base::dec | std::ios_base::fixed;
        break;
    case 'F':
        formatFlags |= std::ios_base::dec | std::ios_base::fixed |
                std::ios_base::uppercase;
        break;
    case 'e':
        formatFlags |= std::ios_base::dec | std::ios_base::scientific;
        break;
    case 'E':
        formatFlags |= std::ios_base::dec | std::ios_base::scientific |
                std::ios_base::uppercase;
        break;
    case 'g':
        formatFlags |= std::ios_base::dec;
        break;
    case 'G':
        formatFlags |= std::ios_base::dec | std::ios_base::uppercase;
        break;
    case 'a':
        formatFlags |= std::ios_base::hex | std::ios_base::scientific;
        break;
    case 'A':
        formatFlags |= std::ios_base::hex | std::ios_base::scientific |
                std::ios_base::uppercase;
        break;
    case 'c':
        break;
    case 's':
        formatFlags |= std::ios_base::boolalpha;
        break;
    case 'p':
        formatFlags |= std::ios_base::hex;
        break;
    case 'n':
        break;
    case '%':
        break;
    default:
        return format + 1;
    }
    return format + 1;
}



#endif // PRINTFPARSER_H
