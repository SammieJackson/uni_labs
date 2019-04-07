#include <string>
#include <limits>
#include <cstdio>
#include "tostring.h"
using namespace std;
#if defined _MSC_VER
    #define PRINT(buffer, format, num) sprintf_s(buffer,sizeof(buffer), format,num)
#else
    #define PRINT(buffer, format, num) sprintf(buffer,format,num)
#endif

string to_string(double num,const char *sf){
	if (sf==NULL ||*sf==0) sf="%.4f";
	char buffer[2*numeric_limits<double>::max_exponent10+4];
    PRINT(buffer,sf,num);
	return string(buffer);
}

#if defined MinGW49
string to_string(long num){
	char buffer[sizeof(long)*8];
    PRINT(buffer,"%ld",num);
	return string(buffer);
}
string to_string(unsigned num){
	char buffer[sizeof(unsigned)*8];
    PRINT(buffer,"%u",num);
	return string(buffer);
}
string to_string(int num){return to_string(long(num));}
#endif
