//Babiienko I. K-11
#include <iostream>
#include <iomanip>

using namespace std;

int main (){
setlocale(0, "Rus");
cout<<"�� �������� ������� ������� ����� �-11 ��ᳺ��� ����."<<endl;
cout<<"���� �������� �� ��������� ���������� ���� ������ � �� �"<<endl;
cout<<"�������� �� �������� �� ����� �������� ������ �*4/7+�."<<endl;
cout<<"���� � �� � ����� ���� ������� �������, ���������� � ����������� ������."<<endl;
cout<<"������ ���� � �� � ����� space:"<<endl;
int x, y;
cin>>x>>y;
if (cin.fail()) cout<<endl<<"�� ����� ��������� ����� ���!"<<endl;
double z;
z=x*(4.0/7)+y;
cout<<"�� ����� ���� � = "<<x<<" �� � = "<<y<<" ."<<endl;
cout<<"�������� ������ �*4/7+� ���� "<<setprecision(5)<<z<<endl;
return 0;
}
