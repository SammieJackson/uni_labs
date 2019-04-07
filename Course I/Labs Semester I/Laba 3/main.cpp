//Babiienko I. K-11
#include <iostream>
#include <iomanip>

using namespace std;

int main (){
setlocale(0, "Rus");
cout<<"Цю програму виконав студент групи К-11 Бабієнко Ілля."<<endl;
cout<<"Дана програма за введеними значеннями двох змінних х та у"<<endl;
cout<<"обчислює та виводить на екран значення виразу х*4/7+у."<<endl;
cout<<"Змінні х та у мають бути дійсними числами, записаними в десятковому вигляді."<<endl;
cout<<"Введіть змінні х та у через space:"<<endl;
int x, y;
cin>>x>>y;
if (cin.fail()) cout<<endl<<"Ви ввели некоректні вхідні дані!"<<endl;
double z;
z=x*(4.0/7)+y;
cout<<"Ви ввели змінні х = "<<x<<" та у = "<<y<<" ."<<endl;
cout<<"Значення виразу х*4/7+у рівне "<<setprecision(5)<<z<<endl;
return 0;
}
