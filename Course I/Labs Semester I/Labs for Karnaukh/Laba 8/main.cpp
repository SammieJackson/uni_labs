//Babiienko I. K-11
#include "copy.h"
#include "matrix.h"
#include "matrixwork.h"
#include <iostream>

using namespace std;

int main(){
setlocale(0, "Rus");
info();
cout<<"Ця програма обчислює суму елементів правого чверть-трикутника попередньо побудованої матриці. Користувач має"<<endl;
cout<<"ввести розмір матриці, і програма порядково заповнить її послідовними натуральними числами починаючи з 1."<<endl;
cout<<"Введіть розмір матриці (додатнє ціле число): ";
int n;
cin>>n;
if ((cin.fail()) || (n<0)) {cout<<endl<<" Некоректний ввід!"<<endl;} else
if (n==0) {cout<<endl<<" Матриця порожня!"<<endl;} else {
const int sizea=n;
int a[maxs][maxs];
create(a, sizea);
vyvid(a, sizea);
cout<<endl<<"Для неї було обчислено суму елементів в правому чверть-трикутнику. Ця сума рівна "<<suma(a, sizea); }
return 0;
}
