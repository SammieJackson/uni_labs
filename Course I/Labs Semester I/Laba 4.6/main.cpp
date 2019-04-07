//Babiienko I. K-11
//#include "copyright.h"
#include <iomanip>
#include "func4.6.h"
#include <cmath>
#include <iostream>

using namespace std;

int main(){
try{
setlocale(0, "Rus");
//info();
cout<<"Ця програма обчислює значення виразу tg(5)+e/x^2 для"<<endl;
cout<<"введеного ненульового дійсного значення змінної х. Введіть х:"<<endl;
double x;
cin>>x;
if (cin.fail()) {cout<<endl<<"Некоректний ввід!"<<endl;}
else {
double z=vyraz(x);
cout<<"Ви ввели значення х = "<<x<<endl;
cout<<"Значення виразу tg(5)+e/x^2 для введеного значення х рівне "<<setprecision(5)<<z;
}
return 0;
}
catch(int n){
if (n==1) cout<<"Некоректний ввiд! Вiдбулось дiлення на 0!";
}
}

