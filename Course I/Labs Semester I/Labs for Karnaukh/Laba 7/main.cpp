// Babiienko I. K-11
#include "copy.h"
#include "array.h"
#include "maxser.h"
#include <iostream>

using namespace std;

int main(){
setlocale(0, "Rus");
info();
cout<<"�� �������� ��������� ������� �������� ��� (��������� ����������� ���������� �������� ������) ��������� ������ ����� �����. ��� ��������� ��� "<<endl;
cout<<"������ ctrl+z �� �������� enter"<<endl;
int sizea=0;
const int maxsize=1000;
int a[maxsize];
vvid(a, maxsize, sizea);
if (sizea==0) {cout<<endl<<" �� ����� ������� ������"<<endl; return 0;}
vyvid(a, sizea);
cout<<endl<<"���� �������� ���� �� ������� "<<maxseries(a, sizea);
return 0;
}
