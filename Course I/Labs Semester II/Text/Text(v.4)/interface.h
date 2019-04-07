//Babiienko I. K-11
#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include <string>
using namespace std;

void info();
void bnf();
void getInFile(int argc, char** argv, string &fileName);
void getOutFile(string &fileName);

#endif // INTERFACE_H_INCLUDED
