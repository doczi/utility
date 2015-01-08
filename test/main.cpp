#include <iostream>
#include <regex>

#include "logger/printfstream.h"


struct Y {};



int main()
{
    int x = 0;
    StreamPrintf(std::cout, "a: %d\nb: %c\nc: %n (other stuff)\nd: %s\ne: %s\nf: %d\n", x, 65, &x, "dkdkd", std::string("string"), 'y');
    StreamPrintf(std::cout, "|%3$-10.1f|", 15, 3, 1.234567);
    std::cout << std::endl << "x: " << x << std::endl;

    return 0;
}

