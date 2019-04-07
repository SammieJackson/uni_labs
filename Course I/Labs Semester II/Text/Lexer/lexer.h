//Babiienko I. K-11
#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

#include <string>
using namespace std;

class Lexer
{
public:
    void saveLine(const string &line);
    bool eol() const; //no symbols left to parse
    string getLexem(); //empty string iff eol
private:
    string currentLine;
    size_t cLineLength;
    size_t currentPosition; //first still not read symbol
};

#endif // LEXER_H_INCLUDED
