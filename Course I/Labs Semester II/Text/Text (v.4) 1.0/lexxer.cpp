#include "lexxer.h"

using std::string;

void Lexer::saveLine(const std::string &line) {
    currentLine=line;
    cLineLength=line.length();
    currentPosition=0;
}

bool Lexer::eol() const { //no symbols left to parse
    return currentPosition==cLineLength;
}

std::string Lexer::getLexem() {//if eol - returns empty string
    if (currentLine=="" || eol()) return "";
    std::string oss;
    size_t i=currentLine.find(";", currentPosition);
    if(i==std::string::npos) {
        oss=currentLine.substr(currentPosition, cLineLength-currentPosition);
        currentPosition=cLineLength;
        return oss;
    }
    oss=currentLine.substr(currentPosition, i-currentPosition);
    currentPosition=i+1;
    return oss;
}
