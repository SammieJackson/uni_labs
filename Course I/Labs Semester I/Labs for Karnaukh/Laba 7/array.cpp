//Babiienko I. K-11
#include "array.h"
#include <iostream>

using namespace std;

void vvid(int a[], const int maxsize, int& sizea){
cout<<"������ ������ ����������� ����� space: "<<endl;
for (int i=0; i<maxsize; i++){
cin>>a[i];
sizea++;
if (cin.eof()) {a[i]=-1; sizea--; return;} else
if (cin.fail()) {cout<<"�� ����� ��������� ���"<<endl; a[i]=-1; sizea--; return;}
}
return;
}


void vyvid(const int a[], const int sizea){
cout<<"�� ����� ��������� ������: ";
for (int i=0; i<sizea; i++){cout<<a[i]; if (i==(sizea-1)) cout<<"."; else cout<<", ";}
cout<<endl;
return;
}
