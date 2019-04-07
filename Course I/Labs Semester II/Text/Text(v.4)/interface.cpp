//Babiienko I. K-11
#include <iostream>
#include <string>

using namespace std;

void info()
{
    cout<<"\n This program reads a file with certain input data: statistics of races of a biatlon championship.\n"
    <<" During reading, white symbols and empty lines are ignored.\n"
    <<" The input file has to have certain structure:\n\n"
    <<"   the header - has to start with \"header:\"\n"
    <<"   the main body - consists of lines with following info:\n"
    <<"     race number (positive integer - not bigger than number from header);\n"
    <<"     participant start number (positive integer);\n"
    <<"     participant rank - place in which he finished the race;\n"
    <<"     participants name, surname and country - have to contain only letters (and these are separate entries)\n"
    <<"     participants overall time for this race (positive integer - because in seconds - can be -1 in case the participant hasn't finish the race);\n"
    <<"     time (positive integer - in seconds from the race start) of starts and finishes of first and second shooting rounds (four separate entries);\n"
    <<"     number of missed shots during this race (positive integer);\n"
    <<"     total amount of time for the penalty laps (positive integer - not bigger than overall time).\n"
    <<"   the footer - starts with \"footer:\"\n\n"
    <<" !!!There has to be at least one empty line after the footer!!!"
    <<" The header contains the total number of races in the championship.\n"
    <<" All separate entries in the main body lines (and footer) have to be separated with \";\".\n"
    <<" The footer contains two numbers: total number of main body lines and total number of missed shots (for all participants and races).\n"
    <<" For each sportsman the program finds his misses to races he participated in ratio (in order to determine who had better aim),\n"
    <<" then it prints those whose ratio is the smallest and highlights the races when the sportsman showed the best time at shooting rounds.\n"
    <<" Then the program prints the result into the file with given name (or to console in case name is empty).\n\n\n";
}

void getInFile(int argc, char** argv, string &fileName)
{
    if(argc==1){cout<<"Please, enter the input file name (with path to the file):"<<endl; getline(cin, fileName); return;}
    else {fileName=""; for(int i=1; i<argc; ++i) {fileName+=argv[i];}}
}

void getOutFile(string &fileName)
{
    cout<<"Where would you like to print the result?"<<endl;
    cout<<"Empty=console output, non-empty=file name."<<endl;
    getline(cin, fileName);
}
