#ifndef BUILDER_H_INCLUDED
#define BUILDER_H_INCLUDED
#include "container.h"
#include "lexxer.h"
#include <fstream>

class Builder
{
public:
    Builder(Championship& container);
    void build(const std::string& fileName); //nothrow; returns true on success

private:
    static const long int minRaceNum=1;
    static const long int minStartNum=1;
    static const long int minTime=0;
    static const long int failTime=-1;
    static const long int minMisses=0;
    Championship& c;
    ifstream inFile;
    Lexer l;
    std::string currLine;
    std::string nextLine;
    int linesRead;
    int currLineNum;
    int addedRaces;
    int maxRaceNum=0;
    long int sumMisses=0;

    long int currRaceNum;
    long int currStartNum;
    std::string currName;
    std::string currSurname;
    std::string currCountry;
    long int currRank;
    long int currMisses;
    long int currOvertime;
    long int currEnt1, currEx1;
    long int currEnt2, currEx2;
    long int currPenalty;

    //bool allEntriesAdded() const; //all items for every race for every sportsman
    void processHeader(); //throw(runtime_error);
    void processBody(); //processFooter inside; throw(runtime_error, out_of_range);
    void processBodyLine(); //in currentLine, throw(runtime_error, out_of_range);
    void addRace(); //from curr... data members to Competition& c; throw(runtime_error, out_of_range);
    void savePositiveNumber(long int& a, const std::string name);//or -1 for overall time; throw(runtime_error, out_of_range);
    void saveOverallTime();
    void saveString(std::string& dest); // throw(runtime_error);
    void checkEntries() const;
    void checkSums(const long int totallines, const long int totalmisses) const;
  //  void saveItem(); // throw(runtime_error);
    void processFooter(); //in currentLine, throw(runtime_error, out_of_range);
    void addEntry();

    std::string trimSpaces(const std::string &s) const; //at beginning and end of s
    bool isWhiteLine(const std::string &line) const; //empty is considered white
    bool isNumber(const std::string &line) const; // true iff consists of digits and optional +- at beginning; empty is not a number
    bool getNonEmptyLine();
    //currentLine=nextLine; puts first non-empty line in nextLine with trimming; true iff success
};


#endif // BUILDER_H_INCLUDED

/*
class Builder
{
public:
    Builder(Championship& comp);
    void build(const string &fileName); //nothrow; returns true on success
private:
    long int numOfRaces=10; //comes from Competition, initialized in constructor
    static const long int minRaceNumber=1;
    static const long int maxMark=10;
    static const long int minMark=0;
    Championship& c;
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
    long int tmpRace;
    long int tmpMark;

    bool allEntriesAdded() const; //all items for every judge for every sportsman
    void processHeader(); //throw(runtime_error);
    void processBody(); //processFooter inside; throw(runtime_error, out_of_range);
    void processBodyLine(); //in currentLine, throw(runtime_error, out_of_range);
    void addEntry(); //from tmp... data members to Competition& c; throw(runtime_error, out_of_range);
    void saveStartNumber(); // throw(runtime_error, out_of_range);
    void saveRace(); // throw(runtime_error, out_of_range);
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
*/
