//Babiienko I, K-11
#ifndef MYEXCEPTIONS_H_INCLUDED
#define MYEXCEPTIONS_H_INCLUDED
#include <exception>
#include <string>

class containerExcept:public std::exception
{
private:
    std::string msg; //message
public:
    containerExcept(const std::string &mess);
    const char* what() const noexcept;
};

class builderExcept:public std::exception
{
private:
    std::string msg;
    int line; //number of line where problem occurred
public:
    builderExcept(const std::string &mess, int lineNum=0);
    const char* what() const noexcept; //if line>0 also returns line
};


#endif // MYEXCEPTIONS_H_INCLUDED
