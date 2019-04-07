#include "container.h"
#include "myExceptions.h"
#include "tostring.h"
#include <iostream>
#include <ostream>
#include <fstream>

DeclaredItems::DeclaredItems():head(nullptr), count(0){}
DeclaredItems::~DeclaredItems(){clear();}
void DeclaredItems::clear()
{
	Node* tmp;
	while (head) {
		tmp=head->next;
		delete head;
		head=tmp;
	}
	count=0;
}
 void DeclaredItems::add(const string &item)
 {
	 head=new Node{item, head};
	 ++count;
}
bool DeclaredItems::find(const string &item) const
{
    Node *tmp;
    for(tmp=head; tmp&&tmp->name!=item; tmp=tmp->next);
    return tmp!=nullptr;
}
int DeclaredItems::getCount() const
{
    return count;
}

//********************************************

Judge::Judge():head(nullptr), count(0){}
Judge::~Judge(){clear();}
void Judge::clear()
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
Judge::Iterator::Iterator(Node *c):current(c){}
Judge::Iterator& Judge::Iterator::operator ++()
{
    if(current) current=current->next; return *this;
}
bool Judge::Iterator::OK() const{return current!=nullptr;}
Judge::Iterator::operator bool() const{ return OK();}
string Judge::Iterator::operator *() const
{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    return current->itemName+": "+to_string(current->mark)+" ";
}
long int Judge::Iterator::getMark() const
{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    return current->mark;
}
Judge::Iterator Judge::find(const string &item) const
{
    Node *tmp;
    for(tmp=head; tmp && tmp->itemName!=item; tmp=tmp->next);
    return Judge::Iterator(tmp);
}
Judge::Iterator Judge::add(const string &item, long int mark)
{
    head=new Node{item,mark,head};
    ++count;
    return Judge::Iterator(head);
}
Judge::Iterator Judge::begin() const {return Judge::Iterator(head);}
string Judge::print() const
{
    Judge::Iterator it=begin();
    string res;
    while(it) {res+=*it; ++it;}
    return res+"\n";
}

//*********************************************

Competition::Competition():head(nullptr), count(0){}
Competition::~Competition(){clear();}
void Competition::clear()
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
long int Competition::getNumJudges() const {return numOfJudges;}
Competition::Iterator::Iterator(Node *c):current(c){}
Competition::Iterator& Competition::Iterator::operator ++()
{
    if(current) current=current->next; return *this;
}
bool Competition::Iterator::OK() const{return current!=nullptr;}
Competition::Iterator::operator bool() const{ return OK();}
string Competition::Iterator::operator *() const
{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    string res=to_string(current->startNumber)+" "+current->name+" "+current->surname+"\n";
    for(int i=0; i<numOfJudges; ++i) res=res+"Judge "+to_string(i+1)+" "+current->judges[i].print();
    return res+"\n";
}

long int Competition::Iterator::getStartNumber() const
{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    return current->startNumber;
}

string Competition::Iterator::getName() const
{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    return current->name;
}

string Competition::Iterator::getSurname() const
{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    return current->surname;
}

double Competition::Iterator::getResult() const
{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    return current->result;
}

long int Competition::Iterator::getSumMarks() const
{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    long int sum=0;
    for(int i=0; i<numOfJudges; ++i) {Judge::Iterator it2=current->judges[i].begin(); while(it2) {sum+=it2.getMark(); ++it2;}}
    return sum;
}

void Competition::Iterator::updateResult()
{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    long int judgeSum[numOfJudges]={};
    for(int i=0; i<numOfJudges; ++i){Judge::Iterator it=current->judges[i].begin(); while(it) {judgeSum[i]=+it.getMark(); ++it;}}
    long int min=judgeSum[0], max=judgeSum[0], sum=judgeSum[0];
    for(int i=1; i<numOfJudges; ++i)
      {if(judgeSum[i]>max) max=judgeSum[i]; else if(judgeSum[i]<min) min=judgeSum[i]; sum+=judgeSum[i];}
    current->result=(sum-max-min)/double(numOfJudges-2);
}

Judge::Iterator Competition::Iterator::findItem(long int judge, const string &name) const
{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    if (judge<1 ||judge>numOfJudges) throw containerExcept("Internal error: passed judge number is out of possible range.");
    return current->judges[judge-1].find(name);
}

Judge::Iterator Competition::Iterator::addItem(long int judge, const string &name, long int mark) const
{
    if(!current) throw containerExcept("Internal error: wrong iterator position.");
    if (judge<1 ||judge>numOfJudges) throw containerExcept("Internal error: passed judge number is out of possible range.");
    return current->judges[judge-1].add(name,mark);
}

Competition::Iterator Competition::find(long int startNumber) const
{
    Node *tmp;
    for(tmp=head; tmp && tmp->startNumber!=startNumber; tmp=tmp->next);
    return Competition::Iterator(tmp);
}

Competition::Iterator Competition::add(long int startNumber, const string &name, const string &surname)
{
    head=new Node{startNumber,name,surname,0.,head};
    ++count;
    return Competition::Iterator(head);
}

Competition::Iterator Competition::begin() const {return Competition::Iterator(head);}

void Competition::addDItem(const string &item){dItems.add(item);}
bool Competition::findDItem(const string &item) const {return bool(dItems.find(item));}
int Competition::getDItemsCount() const {return dItems.getCount();}


void Competition::print() const
{
    Competition::Iterator it=begin();
    cout<<endl;
    while(it) {cout<<*it; ++it;}
}

void Competition::updateResults()
{
    Competition::Iterator it=begin();
    while(it) {it.updateResult(); ++it;}
}

void Competition::sortByResult()
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

void Competition::printResults(const string &fName) const
{
    ostream *f; ofstream g;
    if(fName=="") f=&cout;  else {g.open(fName); f=&g;}
    if(!(*f)) throw containerExcept("Problem with destination file or console. Can't print results.");
    Competition::Iterator it=begin();
    while(it) {*f<<it.getStartNumber()<<"; "<<it.getName()<<"; "<<it.getSurname()<<"; "<<it.getResult()<<endl; ++it;}
}

bool Competition::checkSums(long int numOfParticipants, long int sumOfMarks) const
{
    long int sum=0;
    Competition::Iterator it=begin();
    while(it) {sum+=it.getSumMarks(); ++it;}
    return (count==numOfParticipants && sum==sumOfMarks);
}

int Competition::getCount() const {return count;}

