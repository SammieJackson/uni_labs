//Babiienko I. K-11
#include "copy.h"
#include <iomanip>
#include "func4.6.h"
#include <cmath>
#include <iostream>

using namespace std;

int main(){
setlocale(0, "Rus");
info();
cout<<" �� �������� �������� �������� ������ tg(5)+e/x^2 ���"<<endl;
cout<<"��������� ����������� ������� �������� ����� �. ������ �:"<<endl;
double x;
cin>>x;
if (cin.fail()) {cout<<endl<<"����������� ���!"<<endl;}
else {
try{double z=vyraz(x);
cout<<" �� ����� �������� � = "<<x<<endl;
cout<<" �������� ������ tg(5)+e/x^2 ��� ��������� �������� � ���� "<<setprecision(5)<<z;
}
catch(int n){
if (n==1) cout<<" ����������� ��i�! �i������� �i����� �� 0!";
}
}
return 0;
}

