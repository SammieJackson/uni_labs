//Babiienko I. K-11
#include "copy.h"
#include <iomanip>
#include "func.h"
#include <cmath>
#include <iostream>

using namespace std;

int main(){
setlocale(0, "Rus");
info();
cout<<" Ця програма обчислює значення виразу tg(5)+e/x^2 для"<<endl;
cout<<" введеного ненульового дiйсного значення змiнної х. Введiть х:"<<endl;
double x;
cin>>x;
if ((cin.fail()) || (x==0)) {cout<<endl<<"Некоректний ввiд!"<<endl;}
else {
double z=vyraz(x);
cout<<" Ви ввели значення х = "<<x<<endl;
cout<<" Значення виразу tg(5)+e/(x^2) для введеного значення х рiвне "<<setprecision(5)<<z;
}
return 0;
}
