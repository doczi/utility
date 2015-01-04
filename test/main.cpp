#include <iostream>
#include <regex>

#include "logger/printfstream.h"


struct Y {};



int main()
{
    int x = 0;
    //StreamPrintf(std::cout, "a: %d\nb: %c\nc: %n (other stuff)\nd: %s\ne: %s\nf: %d\n", x, 65, &x, "dkdkd", std::string("string"), 'y');
    StreamPrintf(std::cout, "%1$d %2$d %1$d %2$s %%def", 1, "abc");
    std::cout << std::endl << "x: " << x << std::endl;

    return 0;
}

