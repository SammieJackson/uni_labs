//Babiienko I. K-11
//#include "copy.h"
#include "matrix.h"
#include <iostream>

using namespace std;

int main(){
setlocale(0, "Rus");
//info();
cout<<"�� �������� �������� ���� �������� ������� ������-���������� ���������� ���������� �������. ���������� ��"<<endl;
cout<<"������ ����� �������, � �������� ��������� ��������� �� ����������� ������������ ������� ��������� � 1."<<endl;
cout<<"������ ����� ������� (������ ���� �����): ";
int n;
cin>>n;
if ((cin.fail()) || (n<=0)) cout<<"����������� ���!";
const int sizea=n, maxs=20;
int a[maxs][maxs];
create(a, sizea);
vyvid(a, sizea);
cout<<endl<<"��� �� ���� ��������� ���� �������� � ������� ������-����������. �� ���� ���� "<<suma(a, sizea);
return 0;
}
