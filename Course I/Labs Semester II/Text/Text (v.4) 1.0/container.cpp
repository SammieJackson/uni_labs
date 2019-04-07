#include <sstream>
#include <iostream>
#include <ostream>
#include <fstream>
#include "container.h"
#include "myExceptions.h"
#include "tostring.h"


using std::string;
using namespace std;


Race::Race(long int rnum, long int snum, long int rang, long int misses, long int overtime, long int ent1, long int ex1, long int ent2, long int ex2, long int penalty):
RaceNum(rnum), StartNum(snum), Rank(rang), Misses(misses), OverallTime(overtime),
Enter1(ent1), Exit1(ex1), FireTime1(ex1-ent1),
Enter2(ent2), Exit2(ex2), FireTime2(ex2-ent2),
PenaltyTime(penalty), summFireTime(ex2+ex1-ent2-ent1)
{}

Race::Race(const Race& r):
RaceNum(r.RaceNum), StartNum(r.StartNum), Rank(r.Rank), Misses(r.Misses), OverallTime(r.OverallTime),
Enter1(r.Enter1), Exit1(r.Exit1), FireTime1(r.Exit1-r.Enter1),
Enter2(r.Enter2), Exit2(r.Exit2), FireTime2(r.Exit2-r.Enter2),
PenaltyTime(r.PenaltyTime), summFireTime(r.Exit2+r.Exit1-r.Enter2-r.Enter1)
{}

Race::operator string() const {
    std::ostringstream oss;
    oss<<"  Race number - "<<RaceNum<<";"<<" participant start number - "<<StartNum<<"; rank - "<<Rank<<
    "; total time - ";
    if (OverallTime == -1) oss<<" hasn't finished"; else
    oss<<OverallTime;
    oss<<"; total missed shots - "<<Misses<<".";
    return oss.str();
}

long int Race::getFireTime() const {return summFireTime;}

long int Race::getMisses() const {return Misses;}

//long int Race::getRaceNumber() const {return RaceNum;}

//----------------------------------------------------------------

Participant::Participant():head(nullptr), count(0){}

Participant::Participant(std::string n, std::string s, std::string c){
    name=n;
    surname=s;
    country=c;
    head=nullptr;
    count=0;
}

Participant::~Participant(){clear();}

void Participant::clear(){
    Node *tmp;
    while(head)
    {
        tmp=head->next;
        delete head;
        head=tmp;
    }
    count=0;
    name = surname = country = "";
}

std::string Participant::getAllInfo() const{
    std::ostringstream oss;
    oss<<" Name: "<<name<<"\n Surname: "<<surname<<"\n Country: "<<country<<"\n";
    Participant::Iterator iter=begin();
    while(iter) {oss<<string(iter)<<"\n"; ++iter;}
    return oss.str();
}

double Participant::getMissPercentage() const{return MissPercentage;}

Participant::Iterator::Iterator(Node *c):current(c){}

Participant::Iterator& Participant::Iterator::operator ++(){
    if(current) current=current->next;
    return *this;
}

bool Participant::Iterator::OK() const{
    return current!=nullptr;
}

Participant::Iterator::operator bool() const{
    return OK();
}

/*
string Participant::Iterator::operator *() const{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    return current->itemName+": "+to_string(current->mark)+" ";
}
*/

Participant::Iterator::operator string() const{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    if (current->hasBestTime == 1) return string(current->race)+" <- Best time";
    return string(current->race);
}

void Participant::Iterator::setHasBestTimeToFalse() const{
    current->hasBestTime=false;
}


/*
long int Participant::Iterator::getMark() const{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    return current->mark;
}
*/


Participant::Iterator Participant::find(const long int num) const{
    Node *tmp;
    for(tmp=head; tmp && tmp->racenum != num; tmp=tmp->next);
    return Participant::Iterator(tmp);
}

Participant::Iterator Participant::add(const long int rnum, const Race& r){
    if (head == nullptr) {
        BestFireTime=r.getFireTime();
        head=new Node{rnum,r,true,head};
    } else
    if (r.getFireTime() < BestFireTime) {
        BestFireTime=r.getFireTime();
        Participant::Iterator iter=begin();
        while(iter) {iter.setHasBestTimeToFalse(); ++iter;}
        head=new Node{rnum,r,true,head};
    } else
    if (r.getFireTime() == BestFireTime) head=new Node{rnum,r,true,head}; else {
        head=new Node{rnum,r,false,head};
    }
    ++count;
    TotalRaces = count;
    TotalMisses += r.getMisses();
    MissPercentage = TotalMisses/TotalRaces;
    return Participant::Iterator(head);
}

Participant::Iterator Participant::begin() const {
    return Participant::Iterator(head);
}

//----------------------------------------------------------

Championship::Championship():head(nullptr), count(0){}

Championship::~Championship(){clear();}

void Championship::clear(){
    Node *tmp;
    while(head)
    {
        tmp=head->next;
        delete head;
        head=tmp;
    }
    count=0;
    BestAim=0;
}

Championship::Iterator::Iterator(Node *c):current(c){}

Championship::Iterator& Championship::Iterator::operator ++(){
    if(current) current=current->next;
    return *this;
}

bool Championship::Iterator::OK() const{
    return current!=nullptr;
}

Championship::Iterator::operator bool() const{
    return OK();
}

Championship::Iterator::operator string() const{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    std::ostringstream oss;
    oss<<(current->p.getAllInfo());
    return oss.str();
}

void Championship::Iterator::setHasBestAimToTrue()const{
    current->hasBestAim=true;
}


/*
void Championship::Iterator::updateResult(){
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    long int judgeSum[numOfRaces]={};
    for(int i=0; i<numOfRaces; ++i){Participant::Iterator it=current->races[i].begin(); while(it) {judgeSum[i]=+it.getMark(); ++it;}}
    long int min=judgeSum[0], max=judgeSum[0], sum=judgeSum[0];
    for(int i=1; i<numOfRaces; ++i)
      {if(judgeSum[i]>max) max=judgeSum[i]; else if(judgeSum[i]<min) min=judgeSum[i]; sum+=judgeSum[i];}
    current->result=(sum-max-min)/double(numOfRaces-2);
}
*/

int Championship::Iterator::checkForBestAim(const double aim) const{
    if (current->p.getMissPercentage() < aim) return 1;
    if (current->p.getMissPercentage() == aim) return 0;
    return -1;
}

void Championship::Iterator::setBestAim(double& aim) const{
    aim=current->p.getMissPercentage();
}



double Championship::Iterator::getMissPercentage() const{
    return current->p.getMissPercentage();
}

Championship::Iterator Championship::find(const std::string personal_info) const{
    Node *tmp;
    for(tmp=head; tmp && tmp->personalInfo != personal_info; tmp=tmp->next);
    return Championship::Iterator(tmp);
}

Championship::Iterator Championship::add(const std::string personalinfo, const std::string name, const std::string surname, const std:: string country){
    head=new Node{personalinfo,{name,surname,country},false,head};
    ++count;
    return Championship::Iterator(head);
}

Championship::Iterator Championship::begin() const {
    return Championship::Iterator(head);
}

Championship::operator string() const{
    Championship::Iterator iter=begin();
    std::ostringstream oss;
    while(iter) {if (iter.checkForBestAim(BestAim) == 0) oss<<string(iter)<<"\n\n"; ++iter;}
    return oss.str();
}

/*
void Championship::print() const{
    cout<<string(*this);
}
*/

void Championship::printResults(const std::string &fName) const{
    ostream *f; ofstream g;
    if(fName=="") f=&cout;  else {g.open(fName); f=&g;}
    if(!(*f)) throw containerExcept("Error with destination file or console, can't print results.");
    *f<<string(*this);
}

/*
void Championship::updateResults(){
    Championship::Iterator iter=begin();
    while(iter) {iter.updateResult(); ++iter;}
}
*/

void Championship::findBestAim(){
    Championship::Iterator iter=begin();
    while(iter) {
        if (iter.checkForBestAim(BestAim) == 1) iter.setBestAim(BestAim);
        ++iter;
    }
    while(iter) {
        if (iter.checkForBestAim(BestAim) == 0) iter.setHasBestAimToTrue();
        ++iter;
    }
}

Participant::Iterator Championship::Iterator::findRace(const long int racenum) const {
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    if (racenum<1) throw containerExcept("Internal error: passed race number is out of possible range.");
    Participant::Iterator iter=current->p.find(racenum);
    return iter;
}

Participant::Iterator Championship::Iterator::addRace(const long int rnum, const Race& race) const {
    if (!current) throw containerExcept("Internal error: wrong iterator position.");
    if (rnum<1) throw containerExcept("Internal error: passed race number is out of possible range.");
    return current->p.add(rnum, race);
}














/*
Race::Race():head(nullptr), count(0){}
Race::~Race(){clear();}
void Race::clear()
{
	Node* tmp;
	while (head) {
		tmp=head->next;
		delete head;
		head=tmp;
	}
	count=0;
}
 void Race::add(const string &item)
 {
	 head=new Node{item, head};
	 ++count;
}
bool Race::find(const string &item) const
{
    Node *tmp;
    for(tmp=head; tmp&&tmp->name!=item; tmp=tmp->next);
    return tmp!=nullptr;
}
int Race::getCount() const
{
    return count;
}



Participant::Participant():head(nullptr), count(0){}
Participant::~Participant(){clear();}
void Participant::clear()
{
    Node *tmp;
    while(head)
    {
        tmp=head->next;
        delete head;
        head=tmp;
    }
    count=0;
}
Participant::Iterator::Iterator(Node *c):current(c){}
Participant::Iterator& Participant::Iterator::operator ++()
{
    if(current) current=current->next; return *this;
}
bool Participant::Iterator::OK() const{return current!=nullptr;}
Participant::Iterator::operator bool() const{ return OK();}
string Participant::Iterator::operator *() const
{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    return current->itemName+": "+to_string(current->mark)+" ";
}
long int Participant::Iterator::getMark() const
{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    return current->mark;
}
Participant::Iterator Participant::find(const string &item) const
{
    Node *tmp;
    for(tmp=head; tmp && tmp->itemName!=item; tmp=tmp->next);
    return Participant::Iterator(tmp);
}
Participant::Iterator Participant::add(const string &item, long int mark)
{
    head=new Node{item,mark,head};
    ++count;
    return Participant::Iterator(head);
}
Participant::Iterator Participant::begin() const {return Participant::Iterator(head);}
string Participant::print() const
{
    Participant::Iterator it=begin();
    string res;
    while(it) {res+=*it; ++it;}
    return res+"\n";
}


Championship::Championship():head(nullptr), count(0){}
Championship::~Championship(){clear();}
void Championship::clear()
{
    Node *tmp;
    while(head)
    {
        tmp=head->next;
        delete head;
        head=tmp;
    }
    count=0;
}
long int Championship::getNumRaces() const {return numOfRaces;}
Championship::Iterator::Iterator(Node *c):current(c){}
Championship::Iterator& Championship::Iterator::operator ++()
{
    if(current) current=current->next; return *this;
}
bool Championship::Iterator::OK() const{return current!=nullptr;}
Championship::Iterator::operator bool() const{ return OK();}
string Championship::Iterator::operator *() const
{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    string res=to_string(current->startNumber)+" "+current->name+" "+current->surname+"\n";
    for(int i=0; i<numOfRaces; ++i) res=res+"Judge "+to_string(i+1)+" "+current->races[i].print();
    return res+"\n";
}

long int Championship::Iterator::getStartNumber() const
{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    return current->startNumber;
}

string Championship::Iterator::getName() const
{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    return current->name;
}

string Championship::Iterator::getSurname() const
{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    return current->surname;
}

double Championship::Iterator::getResult() const
{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    return current->result;
}

long int Championship::Iterator::getSumMarks() const
{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    long int sum=0;
    for(int i=0; i<numOfRaces; ++i) {Participant::Iterator it2=current->races[i].begin(); while(it2) {sum+=it2.getMark(); ++it2;}}
    return sum;
}

void Championship::Iterator::updateResult()
{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    long int judgeSum[numOfRaces]={};
    for(int i=0; i<numOfRaces; ++i){Participant::Iterator it=current->races[i].begin(); while(it) {judgeSum[i]=+it.getMark(); ++it;}}
    long int min=judgeSum[0], max=judgeSum[0], sum=judgeSum[0];
    for(int i=1; i<numOfRaces; ++i)
      {if(judgeSum[i]>max) max=judgeSum[i]; else if(judgeSum[i]<min) min=judgeSum[i]; sum+=judgeSum[i];}
    current->result=(sum-max-min)/double(numOfRaces-2);
}

Participant::Iterator Championship::Iterator::findItem(long int race, const string &name) const
{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    if (race<1 ||race>numOfRaces) throw containerExcept("Internal error: passed race number is out of possible range.");
    return current->races[race-1].find(name);
}

Participant::Iterator Championship::Iterator::addItem(long int race, const string &name, long int mark) const
{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    if (race<1 ||race>numOfRaces) throw containerExcept("Internal error: passed race number is out of possible range.");
    return current->races[race-1].add(name,mark);
}

Championship::Iterator Championship::find(long int startNumber) const
{
    Node *tmp;
    for(tmp=head; tmp && tmp->startNumber!=startNumber; tmp=tmp->next);
    return Championship::Iterator(tmp);
}

Championship::Iterator Championship::add(long int startNumber, const string &name, const string &surname)
{
    head=new Node{startNumber,name,surname,0.,head};
    ++count;
    return Championship::Iterator(head);
}

Championship::Iterator Championship::begin() const {return Championship::Iterator(head);}

void Championship::addDItem(const string &item){dItems.add(item);}
bool Championship::findDItem(const string &item) const {return bool(dItems.find(item));}
int Championship::getDItemsCount() const {return dItems.getCount();}


void Championship::print() const
{
    Championship::Iterator it=begin();
    cout<<endl;
    while(it) {cout<<*it; ++it;}
}

void Championship::updateResults()
{
    Championship::Iterator it=begin();
    while(it) {it.updateResult(); ++it;}
}

void Championship::sortByResults()
{
    if(count<2) return;
    bool swapped=true;
    while(swapped)
    {
    swapped=false;
    if(head->result < (head->next)->result) {Node *tmp=head->next; head->next=tmp->next; tmp->next=head; head=tmp; swapped=true;}
    Node *tmp1=head, *tmp2=head->next, *tmp3=(head->next)->next;
    while(tmp3!=nullptr)
        {
         if(tmp2->result < tmp3->result)
         {
             Node *tmp=tmp3; tmp2->next=tmp3->next; tmp->next=tmp2; tmp1->next=tmp; swapped=true;
         }
         tmp1=tmp1->next; tmp2=tmp1->next; tmp3=tmp2->next;
        }
    }
}

void Championship::printResults(const string &fName) const
{
    ostream *f; ofstream g;
    if(fName=="") f=&cout;  else {g.open(fName); f=&g;}
    if(!(*f)) throw containerExcept("Problem with destination file or console. Can't print results.");
    Championship::Iterator it=begin();
    while(it) {*f<<it.getStartNumber()<<"; "<<it.getName()<<"; "<<it.getSurname()<<"; "<<it.getResult()<<endl; ++it;}
}

bool Championship::checkSums(long int numOfParticipants, long int sumOfMarks) const
{
    long int sum=0;
    Championship::Iterator it=begin();
    while(it) {sum+=it.getSumMarks(); ++it;}
    return (count==numOfParticipants && sum==sumOfMarks);
}

int Championship::getCount() const {return count;}

*/
