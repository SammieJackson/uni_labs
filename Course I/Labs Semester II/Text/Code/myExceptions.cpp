#include "myExceptions.h"
#include "MyLib.h"

containerExcept::containerExcept(const std::string &mess):msg(mess){}
const char* containerExcept::what() const noexcept {return msg.c_str();}

builderExcept::builderExcept(const std::string &mess, int lineNum):msg(mess), line(lineNum){}
const char* builderExcept::what() const noexcept
{
    std::string report=msg;
    if(line>0) report=report+"\nProblem at line "+to_string(line)+".";
    return report.c_str();
}
