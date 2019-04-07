//this code was created by K-12 student Ivan Yakovlev
#ifndef BUILDER_H_INCLUDED
#define BUILDER_H_INCLUDED
#include "container.h"
#include "lexer.h"
#include <fstream>
class Builder
{
public:
    Builder(Competition& comp);
    void build(const string &fileName); //nothrow; returns true on success
private:
    long int numOfJudges=10; //comes from Competition, initialized in constructor
    static const long int minJudgeNumber=1;
    static const long int maxMark=10;
    static const long int minMark=0;
    Competition& c;
    ifstream inFile;
    Lexer l;
    string currLine;
    string nextLine;
    int linesRead;
    int currLineNum;
    int addedEntriesCount;

    long int tmpStartNumber;
    string tmpName;
    string tmpSurname;
    string tmpItem;
    long int tmpJudge;
    long int tmpMark;

    bool allEntriesAdded() const; //all items for every judge for every sportsman
    void processHeader(); //throw(runtime_error);
    void processBody(); //processFooter inside; throw(runtime_error, out_of_range);
    void processBodyLine(); //in currentLine, throw(runtime_error, out_of_range);
    void addEntry(); //from tmp... data members to Competition& c; throw(runtime_error, out_of_range);
    void saveStartNumber(); // throw(runtime_error, out_of_range);
    void saveJudge(); // throw(runtime_error, out_of_range);
    void saveMark(); // throw(runtime_error, out_of_range);
    void saveString(string &dest); // throw(runtime_error);
    void saveItem(); // throw(runtime_error);
    void processFooter(); //in currentLine, throw(runtime_error, out_of_range);

    string trimSpaces(const string &s) const; //at beginning and end of s
    bool isWhiteLine(const string &line) const; //empty is considered white
    bool isNumber(const string &line) const; // true iff consists of digits and optional +- at beginning; empty is not a number
    bool getNonEmptyLine();
    //currentLine=nextLine; puts first non-empty line in nextLine with trimming; true iff success
};

#endif // BUILDER_H_INCLUDED
