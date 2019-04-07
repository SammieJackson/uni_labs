#include <iostream>
#include "laba.h"
#include <string>
#include "help.h"
//#include "copy.h"


using namespace std;

int main()
{
    //info();
    string numb;
    setlocale(0, "Rus");
    cout << " Enter command (number of laba): ";
    cin>>numb;
    if (cin.fail()) {cout<<endl<<"ERROR!"; return 0;}
    if (numb=="laba5") laba5();
    if (numb=="laba6") laba6();
    if (numb=="laba7") laba7();
    if (numb=="laba8") laba8();
    if (numb=="help") help();
    return 0;
}
