//this code was created by K-12 student Ivan Yakovlev
#include "builder.h"
#include <cctype>   // for functions isspace, isdigit
#include <cstdlib> // for strtol
#include <stdexcept>
#include "myExceptions.h"
Builder::Builder(Competition& comp):numOfJudges(comp.getNumJudges()), c(comp), linesRead(0), currLineNum(0), addedEntriesCount(0){}


void Builder::build(const string &fileName)
{
    inFile.open(fileName);
    if(!inFile) throw builderExcept("Unable to open file.");
    if(inFile.eof()) throw builderExcept("The file is empty.");
    processHeader();
    processBody(); //processFooter inside
    if(!allEntriesAdded()) throw builderExcept("Not all entries found.");
    inFile.close();
}
bool Builder::allEntriesAdded() const
{
    return addedEntriesCount==((c.getCount()*numOfJudges)*c.getDItemsCount());
}

void Builder::processHeader()
{
    if(!getNonEmptyLine()) throw builderExcept("File consists of only whites.");
    if(!getNonEmptyLine()) throw builderExcept("No body/footer detected.");
    l.saveLine(currLine);
    string tmp;
    while(!l.eol())
    {
        tmp=trimSpaces(l.getLexem());
        if(tmp=="" || (l.eol() && currLine.back()==';'))
            throw builderExcept("Empty item in header or ';' after last item.", currLineNum);
         else {if (!c.findDItem(tmp)) c.addDItem(tmp);
               else throw builderExcept("Double definition of item in header.", currLineNum);}
    }
}

void Builder::processBody()
{
    if(!getNonEmptyLine()) throw builderExcept("The body is empty - nothing to process.", currLineNum);
    do processBodyLine(); while(getNonEmptyLine());
    processFooter();
}

void Builder::processBodyLine()
{
    l.saveLine(currLine);
    saveStartNumber();
    saveString(tmpName);
    saveString(tmpSurname);
    saveJudge();
    saveItem();
    saveMark();
    if(!l.eol() || (l.eol() && currLine.back()==';'))
        throw builderExcept("Too many entries in line or ';' after last data.", currLineNum);
    addEntry();
}

void Builder::addEntry()
{
    Competition::Iterator it=c.find(tmpStartNumber);
    if(it) {if(it.getName()!=tmpName || it.getSurname()!=tmpSurname) throw builderExcept("Redefinition of sportsman.", currLineNum);}
      else it=c.add(tmpStartNumber, tmpName, tmpSurname);
    Judge::Iterator it2=it.findItem(tmpJudge, tmpItem);
    if(it2) throw builderExcept("Redefinition of mark.", currLineNum);
    it.addItem(tmpJudge, tmpItem, tmpMark);
    ++addedEntriesCount;
}

void Builder::saveStartNumber()
{
    if(l.eol()) throw builderExcept("Too few entries in line.", currLineNum);
    string tmp=trimSpaces(l.getLexem());
    if(!isNumber(tmp)) throw builderExcept("Start number is not a number.", currLineNum);
     else
     {
         errno=0;
         tmpStartNumber=strtol(tmp.c_str(), nullptr, 10);
         if(errno==ERANGE) throw builderExcept("Start number is too large.", currLineNum);
     }
    if(tmpStartNumber<1) throw builderExcept("Start number is out of possible range.", currLineNum);
}

void Builder::saveMark()
{
    if(l.eol()) throw builderExcept("Too few entries in line.", currLineNum);
    string tmp=trimSpaces(l.getLexem());
    if(!isNumber(tmp)) throw builderExcept("Mark is not a number.", currLineNum);
     else
     {
         errno=0;
         tmpMark=strtol(tmp.c_str(), nullptr, 10);
         if(errno==ERANGE) throw builderExcept("Mark is too large.", currLineNum);
     }
    if(tmpMark<minMark || tmpMark>maxMark) throw builderExcept("Mark is out of possible range.", currLineNum);
}

void Builder::saveJudge()
{
    if(l.eol()) throw builderExcept("Too few entries in line.", currLineNum);
    string tmp=trimSpaces(l.getLexem());
    if(!isNumber(tmp)) throw builderExcept("Judge number is not a number.", currLineNum);
     else
     {
         errno=0;
         tmpJudge=strtol(tmp.c_str(), nullptr, 10);
         if(errno==ERANGE) throw builderExcept("Judge number is too large.", currLineNum);
     }
    if(tmpJudge<minJudgeNumber || tmpJudge>numOfJudges)
        throw builderExcept("Number of judge is out of possible range.", currLineNum);
}

void Builder::saveString(string &dest)
{
    if(l.eol()) throw builderExcept("Too few entries in line.", currLineNum);
    string tmp=trimSpaces(l.getLexem());
    if(tmp!="") dest=tmp;
     else throw builderExcept("Empty word or word of whites.", currLineNum);
}

void Builder::saveItem()
{
    if(l.eol()) throw builderExcept("Too few entries in line.", currLineNum);
    string tmp=trimSpaces(l.getLexem());
    if(tmp!="") {if(c.findDItem(tmp)) tmpItem=tmp; else throw builderExcept("No such item declared in header.", currLineNum);}
     else throw builderExcept("Empty word or word of whites.", currLineNum);
}

void Builder::processFooter()
{
    int numOfParticipants, sumOfMarks;
    l.saveLine(currLine);

    string tmp=trimSpaces(l.getLexem());
    if(!isNumber(tmp)) throw builderExcept("Not a number in footer.", currLineNum);
     else{ errno=0; numOfParticipants=strtol(tmp.c_str(), nullptr, 10);
           if(errno==ERANGE) throw builderExcept("Footer number is too large.", currLineNum);}
    if(l.eol()) throw builderExcept("Incomplete footer.", currLineNum);

    tmp=trimSpaces(l.getLexem());
    if(!isNumber(tmp)) throw builderExcept("Not a number in footer.", currLineNum);
     else{ errno=0; sumOfMarks=strtol(tmp.c_str(), nullptr, 10);
           if(errno==ERANGE) throw builderExcept("Footer number is too large.", currLineNum);}
    if(!l.eol() || (l.eol() && currLine.back()==';')) throw builderExcept("Extra info in footer or ';' after last data.", currLineNum);
    if(!c.checkSums(numOfParticipants, sumOfMarks)) throw builderExcept("Body data doesn't match footer's checksums.", currLineNum);
}

string Builder::trimSpaces(const string &s) const
{
    if (isWhiteLine(s)) return "";
    int i=0, j=s.length()-1;
    while(isspace(s[i])) ++i;
    while(isspace(s[j])) --j;
    return s.substr(i, j-i+1);
}

bool Builder::isWhiteLine(const string &line) const
{
    int length=line.length(), i;
    for(i=0; i<length && isspace(line[i]); ++i);
    return i==length;
}

bool Builder::isNumber(const string &line) const
{
    int length=line.length(), i;
    if(length==0) return false;
    if(length==1) return isdigit(line[0]);
    if(line[0]!='+' && line[0] !='-' && !isdigit(line[0])) return false;
    for(i=1; i<length && isdigit(line[i]); ++i);
    return i==length;
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

