//Babiienko I. K-11
#include "array.h"
#include <iostream>

using namespace std;

void vvid(int a[], int maxsize, int& sizea){
cout<<"������ ������ ����������� ����� space: "<<endl;
for (int i=0; i<maxsize; i++){
cin>>a[i];
sizea++;
if (cin.eof()) {a[i]=-1; sizea--; return;} else
if (cin.fail()) {cout<<"�� ����� ��������� ���"<<endl; a[i]=-1; sizea--; return;}
}
return;
}

void vyvid(int a[], int sizea){
cout<<"�� ����� ��������� ������: ";
for (int i=0; i<sizea; i++){cout<<a[i]<<" ";}
return;
}

int mini(int a[], int sizea){
int mini=INT_MAX;
for (int i=0; i<sizea; i++){if ((a[i]>=0) && (mini>a[i])) mini=a[i];}
return mini;
}
