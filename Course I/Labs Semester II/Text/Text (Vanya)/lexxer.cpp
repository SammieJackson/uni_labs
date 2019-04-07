#include "lexxer.h"

void Lexer::saveLine(const string &line)
{
    currentLine=line;
    cLineLength=line.length();
    currentPosition=0;
}

bool Lexer::eol() const //no symbols left to parse
{
    return currentPosition==cLineLength;
}

string Lexer::getLexem() //if eol - returns empty string
{
    if (currentLine=="" || eol()) return "";
    string tmp;
    size_t i=currentLine.find(";", currentPosition);
    if(i==string::npos) {
        tmp=currentLine.substr(currentPosition, cLineLength-currentPosition);
        currentPosition=cLineLength;
        return tmp;
    }
    tmp=currentLine.substr(currentPosition, i-currentPosition);
    currentPosition=i+1;
    return tmp;
}
