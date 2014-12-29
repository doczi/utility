#ifndef FORMATTER_H
#define FORMATTER_H

#include <cassert>
#include <ostream>
#include <stdexcept>



class Formatter
{
public:
    Formatter(std::ostream& stream, const char* format);
    template<typename T, typename... Args>
    void write(const T& value, Args&&... args);
    void write();
private:
    enum State {
        START,
        FLAGS,
        WIDTH,
        PRECISION,
        LENGTH,
        SPECIFIER,
        VALUE
    };

    int mNumber;
    State mState;
    std::ostream& mStream;
    const char* mInput;
};



inline Formatter::Formatter(std::ostream& stream, const char* format):
    mNumber(0),
    mState(START),
    mStream(stream),
    mInput(format)
{}



inline void Formatter::write()
{
    while (*mInput) {
        if (*mInput == '%') {
            if (*(mInput + 1) == '%') {
                ++mInput;
            } else {
                throw std::runtime_error(
                        "Invalid format string: missing arguments.");
            }
        }
        mStream.put(*mInput++);
    }
}



template<typename T, typename... Args>
void Formatter::write(const T& value, Args&&... args)
{
    /*
     * This state machine is intentionally implemented as one long function.
     * Breaking it up would not make understanding or testing it easier.
     */

    for (;;) {
        switch (mState) {
        case START:
            switch (*mInput) {
            case '%':
                mState = FLAGS;
                break;
            case '\0':
                return;
            default:
                mStream.put(*mInput);
                break;
            }
            break;

        case FLAGS:
            switch (*mInput) {
            case '-':
                mStream.setf(std::ios_base::left);
                break;
            case '+':
                mStream.setf(std::ios_base::showpos);
                break;
            case ' ':
                /* TODO */
                break;
            case '#':
                mStream.setf(std::ios_base::showbase);
                break;
            case '0':
                mStream.fill('0');
                break;
            default:
                mState = WIDTH;
                --mInput;
                break;
            }
            break;

        case WIDTH:
            switch (*mInput) {
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
                mNumber = 10 * mNumber + (*mInput - '0');
                break;
            case '*':
                mNumber = *reinterpret_cast<const int*>(&value);
                write(args...);
                return;
            case '.':
                mStream.width(mNumber);
                mNumber = 0;
                mState = PRECISION;
                break;
            default:
                mStream.width(mNumber);
                mNumber = 0;
                mState = LENGTH;
                --mInput;
                break;
            }
            break;

        case PRECISION:
            switch (*mInput) {
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
                mNumber = 10 * mNumber + (*mInput - '0');
                break;
            case '*':
                mNumber = *reinterpret_cast<const int*>(&value);
                ++mInput;
                write(args...);
                return;
            default:
                mStream.precision(mNumber);
                mNumber = 0;
                mState = LENGTH;
                --mInput;
                break;
            }
            break;

        case LENGTH:
            switch (*mInput) {
            case 'h':
            case 'l':
            case 'j':
            case 'z':
            case 't':
            case 'L':
                break;
            default:
                mState = SPECIFIER;
                --mInput;
            }
            break;

        case SPECIFIER:
            switch (*mInput) {
            case '%':
                mStream.put('%');
                mState = START;
                break;
            case 'd':
            case 'i':
            case 'u':
                mStream.setf(std::ios_base::dec);
                mState = VALUE;
                break;
            case 'o':
                mStream.setf(std::ios_base::oct);
                mState = VALUE;
                break;
            case 'x':
                mStream.setf(std::ios_base::hex);
                mStream.unsetf(std::ios_base::uppercase);
                mState = VALUE;
                break;
            case 'X':
                mStream.setf(std::ios_base::hex);
                mStream.setf(std::ios_base::uppercase);
                mState = VALUE;
                break;
            case 'f':
                mStream.setf(std::ios_base::fixed);
                mStream.unsetf(std::ios_base::uppercase);
                mState = VALUE;
                break;
            case 'F':
                mStream.setf(std::ios_base::fixed);
                mStream.setf(std::ios_base::uppercase);
                mState = VALUE;
                break;
            case 'e':
                mStream.setf(std::ios_base::dec);
                mStream.setf(std::ios_base::scientific);
                mStream.unsetf(std::ios_base::uppercase);
                mState = VALUE;
                break;
            case 'E':
                mStream.setf(std::ios_base::dec);
                mStream.setf(std::ios_base::scientific);
                mStream.setf(std::ios_base::uppercase);
                mState = VALUE;
                break;
            case 'g':
                mStream.setf(std::ios_base::dec);
                mStream.unsetf(std::ios_base::fixed);
                mStream.unsetf(std::ios_base::scientific);
                mStream.unsetf(std::ios_base::uppercase);
                mState = VALUE;
                break;
            case 'G':
                mStream.setf(std::ios_base::dec);
                mStream.unsetf(std::ios_base::fixed);
                mStream.unsetf(std::ios_base::scientific);
                mStream.setf(std::ios_base::uppercase);
                mState = VALUE;
                break;
            case 'a':
                mStream.setf(std::ios_base::hex);
                mStream.setf(std::ios_base::scientific);
                mStream.unsetf(std::ios_base::uppercase);
                mState = VALUE;
                break;
            case 'A':
                mStream.setf(std::ios_base::hex);
                mStream.setf(std::ios_base::scientific);
                mStream.setf(std::ios_base::uppercase);
                mState = VALUE;
                break;
            default:
                mState = VALUE;
                break;
            }
            break;

        case VALUE:
            mStream << value;
            mStream.flags(std::ios_base::fmtflags());
            mState = START;
            write(args...);
            return;

        default:
            assert(false);
            break;
        }

        ++mInput;
    }

    //throw std::logic_error("Extra arguments provided to write.");
}



#endif // FORMATTER_H

