//Babiienko, K-11
#ifndef TOSTRING_H_INCLUDED
#define TOSTRING_H_INCLUDED
#include <string>
#if defined MinGW49
    std::string to_string(long);
    std::string to_string(int);
    std::string to_string(unsigned);
#endif
    std::string to_string(double, const char *sf="%.4f");
#endif // TOSTRING_H_INCLUDED
