//Babiienko I. K-11
#include "copy.h"
#include "matrix.h"
#include "matrixwork.h"
#include <iostream>

using namespace std;

int main(){
setlocale(0, "Rus");
info();
cout<<"�� �������� �������� ���� �������� ������� ������-���������� ���������� ���������� �������. ���������� ��"<<endl;
cout<<"������ ����� �������, � �������� ��������� ��������� �� ����������� ������������ ������� ��������� � 1."<<endl;
cout<<"������ ����� ������� (������ ���� �����): ";
int n;
cin>>n;
if ((cin.fail()) || (n<0)) {cout<<endl<<" ����������� ���!"<<endl;} else
if (n==0) {cout<<endl<<" ������� �������!"<<endl;} else {
const int sizea=n;
int a[maxs][maxs];
create(a, sizea);
vyvid(a, sizea);
cout<<endl<<"��� �� ���� ��������� ���� �������� � ������� ������-����������. �� ���� ���� "<<suma(a, sizea); }
return 0;
}
