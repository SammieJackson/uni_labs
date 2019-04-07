//Babiienko I, K-11
#include <cctype>   // for functions isspace, isdigit
#include <cstdlib>  // for strtol
#include <sstream>
#include <stdexcept>
#include <iostream>
#include "tostring.h"
#include "builder.h"
#include "myExceptions.h"


Builder::Builder(Championship& container):c(container), linesRead(0), currLineNum(0), addedRaces(0)
{}

void Builder::build(const std::string& fileName) {
    inFile.open(fileName);
    if(!inFile) throw builderExcept("Unable to open file.");
    if(inFile.eof()) throw builderExcept("The file is empty.");
    processHeader();
    processBody(); //processFooter inside
    inFile.close();
}


std::string Builder::trimSpaces(const std::string& s) const {
    if (isWhiteLine(s)) return "";
    int i=0, j=s.length()-1;
    while(isspace(s[i])) ++i;
    while(isspace(s[j])) --j;
    return s.substr(i, j-i+1);
}

bool Builder::isWhiteLine(const std::string& line) const {
    int length=line.length(), i;
    for(i=0; i<length && isspace(line[i]); ++i);
    return i == length;
}

bool Builder::isNumber(const std::string& line) const {
    int length=line.length(), i;
    if(length == 0) return false;
    for(i=0; i<length && isdigit(line[i]); ++i);
    return i == length;
}

bool Builder::getNonEmptyLine()
{
    if(!inFile || inFile.eof()) return false;
    currLine=nextLine; currLineNum=linesRead;
    do {getline(inFile, nextLine); ++linesRead;}
       while(inFile && !inFile.eof() && isWhiteLine(nextLine));
    nextLine=trimSpaces(nextLine);
    return nextLine!="";
}


void Builder::processHeader() {
    if(!getNonEmptyLine()) throw builderExcept("File contains  only white symbols.");
    if(!getNonEmptyLine()) throw builderExcept("No body/footer detected.");
    l.saveLine(currLine);
    std::string tmp;
    if (!l.eol()) {
    tmp=trimSpaces(l.getLexem());

    std::string head="header:";
    bool ok=1;
    for(int i=0; i<7; i++){if (tmp[i]!=head[i]) ok=0;}
    if (ok==0) throw builderExcept("No header found.", currLineNum);
    tmp=trimSpaces(tmp.substr(7,tmp.length()-7));

    if(tmp=="" || (l.eol() && currLine.back()==';')) throw builderExcept("Empty item in header or ';' after last item.", currLineNum);

    if (!isNumber(tmp)) throw builderExcept("Invalid header. No number in header.", currLineNum);
    errno=0;
    maxRaceNum=strtol(tmp.c_str(), nullptr, 10);
    if(errno==ERANGE) throw builderExcept("Total number of races is too large.", currLineNum);
    }
}

void Builder::processBody() {
    if(!getNonEmptyLine()) throw builderExcept("The body is empty - nothing to process.", currLineNum);
    do processBodyLine(); while(getNonEmptyLine());
    processFooter();
}

void Builder::processFooter() {
    int numOfLines, sumOfMisses;
    //if (!getNonEmptyLine()) throw builderExcept("No footer found.", currLineNum);
    l.saveLine(currLine);

    std::string tmp;
    if (!l.eol()){
    tmp=trimSpaces(l.getLexem());

    std::string foot="footer:";
    bool ok=1;
    for(int i=0; i<7; i++){if (tmp[i]!=foot[i]) ok=0;}
    if (ok==0) throw builderExcept("No footer found.", currLineNum);
    tmp=trimSpaces(tmp.substr(7,tmp.length()-7));

    if(!isNumber(tmp)) throw builderExcept("Not a number in footer.", currLineNum);
    else{ errno=0; numOfLines=strtol(tmp.c_str(), nullptr, 10);
    if(errno==ERANGE) throw builderExcept("Footer number is too large.", currLineNum);}
    if(l.eol()) throw builderExcept("Incomplete footer.", currLineNum);
    }

    if (!l.eol()){
    tmp=trimSpaces(l.getLexem());
    if(!isNumber(tmp)) throw builderExcept("Not a number in footer.", currLineNum); else {
        errno=0; sumOfMisses=strtol(tmp.c_str(), nullptr, 10);
        if(errno==ERANGE) throw builderExcept("Footer number is too large.", currLineNum);
    }
    if(!l.eol() || (l.eol() && currLine.back()==';')) throw builderExcept("Extra info in footer or ';' after last data.", currLineNum);
    checkSums(numOfLines, sumOfMisses);
    }
}

void Builder::processBodyLine() {
    l.saveLine(currLine);
    savePositiveNumber(currRaceNum, "race number");
    savePositiveNumber(currStartNum, "participant start number");
    savePositiveNumber(currRank, "participant rank");
    saveString(currSurname);
    saveString(currName);
    saveString(currCountry);
    saveOverallTime();
    savePositiveNumber(currEnt1, "first shooting round entry time");
    savePositiveNumber(currEx1, "first shooting round exit time");
    savePositiveNumber(currEnt2, "second shooting round entry time");
    savePositiveNumber(currEx2, "second shooting round exit time");
    savePositiveNumber(currMisses, "number of missed shots");
    savePositiveNumber(currPenalty, "penalty time");
    if(!l.eol() || (l.eol() && currLine.back()==';')) throw builderExcept("Too many entries in line or ';' after last data.", currLineNum);
    checkEntries();
    sumMisses += currMisses;
    addRace();
}

void Builder::addRace() {
    std::ostringstream personinfo;
    personinfo<<currName<<currSurname<<currCountry;
    Championship::Iterator iter=c.find(personinfo.str());
    if(!iter) {iter=c.add(personinfo.str(), currName, currSurname, currCountry);}
    Participant::Iterator partit=iter.findRace(currRaceNum);
    if(partit) throw builderExcept("Sportsmen "+currSurname+" "+currName+" participated twice in race with number "+to_string(currRaceNum)+".", currLineNum);
    Race currace(currRaceNum, currStartNum, currRank, currMisses, currOvertime, currEnt1, currEx1, currEnt2, currEx2, currPenalty);
    iter.addRace(currRaceNum, currace);
    ++addedRaces;
}

void Builder::saveString(std::string& dest) {
    if(l.eol()) throw builderExcept("Too few entries in line.", currLineNum);
    std::string tmp=trimSpaces(l.getLexem());
    if(tmp!="") dest=tmp;
     else throw builderExcept("Empty word or word of whites.", currLineNum);
}

void Builder::savePositiveNumber(long int& num, const std::string name) {
    if(l.eol()) throw builderExcept("Too few entries in line.", currLineNum);
    std::string tmp=trimSpaces(l.getLexem());
    if(!isNumber(tmp)) throw builderExcept("Entry ("+name+") is not a number.", currLineNum);
     else
     {
         errno=0;
         num=strtol(tmp.c_str(), nullptr, 10);
         if(errno==ERANGE) throw builderExcept("Number entry ("+name+") is too large.", currLineNum);
     }
    if(num<1) throw builderExcept("Number entry ("+name+") is out of possible range.", currLineNum);
}

void Builder::saveOverallTime() {
    if(l.eol()) throw builderExcept("Too few entries in line.", currLineNum);
    std::string tmp=trimSpaces(l.getLexem());
    if(!isNumber(tmp)) throw builderExcept("Overall time is not a number.", currLineNum);
     else
     {
         errno=0;
         currOvertime=strtol(tmp.c_str(), nullptr, 10);
         if(errno==ERANGE) throw builderExcept("Overall time entry is too large.", currLineNum);
     }
    if(currOvertime<1 && currOvertime != -1) throw builderExcept("Overall time is out of possible range.", currLineNum);
}

void Builder::checkEntries() const{
    if (currRaceNum > maxRaceNum) throw builderExcept("Race number is larger than the overall number of races.", currLineNum);
    if (currEnt1 >= currOvertime) throw builderExcept("Entry time of the first shooting round is larger that overall race time.", currLineNum);
    if (currEx1 <= currEnt1) throw builderExcept("Exit time from first shooting round is smaller than entry time of the same round.", currLineNum);
    if (currEnt2 <= currEx1) throw builderExcept("Exit time from first shooting round is larger than entry time of the second round.", currLineNum);
    if (currEx2 <= currEnt2) throw builderExcept("Exit time from second shooting round is smaller than entry time of the same round.", currLineNum);
    if (currOvertime <= currPenalty && currOvertime != -1) throw builderExcept("Penalty time is larger than overall time.", currLineNum);
}

void Builder::checkSums(const long int totallines, const long int totalmisses) const{
    if (totallines != addedRaces) throw builderExcept("Invalid total number of entry lines.", currLineNum);
    if (totalmisses != sumMisses) throw builderExcept("Invalid total number of misses.", currLineNum);
}
