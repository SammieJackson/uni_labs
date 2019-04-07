//this code was created by K-12 student Ivan Yakovlev
#include <iostream>
#include <string>

using namespace std;

void info()
{
    cout<<"This program reads a file(with predetermined BNF, see below)"<<endl;
    cout<<"that contains results of evaluation of sportsmen by each of 10 judges,"<<endl;
    cout<<"according to items declared in header."<<endl;
    cout<<"For each sportsman for each judge sum of marks is evaluated, we get 10 sums."<<endl;
    cout<<"The result of the sportsman is the arithmetic mean of all sums except the smallest and the biggest."<<endl;
    cout<<"This program outputs the sorted (non-decreasing) list of sportsman by their results."<<endl<<endl;

}

void bnf()
{
    cout<<"BNF of input and output:"<<endl;
    cout<<"<INPUT>::= <HEADER><EOL><BODY><FOOTER>"<<endl;
    cout<<"<HEADER>::= <>|<ITEM>|<HEADER><HEADER>"<<endl;
    cout<<"<BODY>::=<>|<ENTRY>|<BODY><BODY>"<<endl;
    cout<<"<ENTRY>::= <START NUMBER>\";\"<SURNAME>\";\"<NAME>\";\"<JUDGE>\";\"<ITEM>\";\"<MARK><EOL>"<<endl;
    cout<<"<FOOTER>::= <NUMBER OF PARTICIPANTS>\";\"<SUM OF MARKS>"<<endl;
    cout<<"****************************************************"<<endl;
    cout<<"<OUTPUT>::=<>|<ENTRY>|<OUTPUT><OUTPUT>"<<endl;
    cout<<"<ENTRY>::=<START NUMBER>\";\"<SURNAME>\";\"<NAME>\";\"<RESULT><EOL>"<<endl<<endl;
}

void getInFile(int argc, char** argv, string &fileName)
{
    if(argc==1){cout<<"Please, enter the input file name:"<<endl; getline(cin, fileName); return;}
    else {fileName=""; for(int i=1; i<argc; ++i) {fileName+=argv[i];}}
}

void getOutFile(string &fileName)
{
    cout<<"Where would you like to print the result?"<<endl;
    cout<<"Empty=console output, non-empty=file name."<<endl;
    getline(cin, fileName);
}
