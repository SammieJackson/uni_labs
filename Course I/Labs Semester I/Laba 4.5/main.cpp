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
cout<<" �� �������� �������� �������� ������ tg(5)+e/x^2 ���"<<endl;
cout<<" ��������� ����������� �i������ �������� ��i��� �. ����i�� �:"<<endl;
double x;
cin>>x;
if ((cin.fail()) || (x==0)) {cout<<endl<<"����������� ��i�!"<<endl;}
else {
double z=vyraz(x);
cout<<" �� ����� �������� � = "<<x<<endl;
cout<<" �������� ������ tg(5)+e/(x^2) ��� ��������� �������� � �i��� "<<setprecision(5)<<z;
}
return 0;
}
