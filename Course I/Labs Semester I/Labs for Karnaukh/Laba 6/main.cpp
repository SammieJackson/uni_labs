//Babiienko I. K-11
#include "copy.h"
#include "array.h"
#include "miniel.h"
#include <iostream>

using namespace std;

int main(){
setlocale(0, "Rus");
info();
cout<<"�� �������� ��������� �������� ���������� ����'������ �������� ��������� ������ ����� �����. ��� ��������� �������� ������ ������ ctrl+z �� ��������� enter."<<endl;
int sizea=0;
const int maxsize=1000;
int a[maxsize];
vvid(a, maxsize, sizea);
if (sizea==0) {cout<<endl<<"�� ����� �������� ������"; return 0;}
vyvid(a, sizea);
cout<<"���� ��������� ���i�'����� ������� �i���� "<<mini(a, sizea);
return 0;
}
