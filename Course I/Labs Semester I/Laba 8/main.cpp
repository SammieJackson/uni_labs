//Babiienko I. K-11
//#include "copy.h"
#include "matrix.h"
#include <iostream>

using namespace std;

int main(){
setlocale(0, "Rus");
//info();
cout<<"Ця програма обчислює суму елементів правого чверть-трикутника попередньо побудованої матриці. Користувач має"<<endl;
cout<<"ввести розмір матриці, і програма порядково заповнить її послідовними натуральними числами починаючи з 1."<<endl;
cout<<"Введіть розмір матриці (додатнє ціле число): ";
int n;
cin>>n;
if ((cin.fail()) || (n<=0)) cout<<"Некоректний ввід!";
const int sizea=n, maxs=20;
int a[maxs][maxs];
create(a, sizea);
vyvid(a, sizea);
cout<<endl<<"Для неї було обчислено суму елементів в правому чверть-трикутнику. Ця сума рівна "<<suma(a, sizea);
return 0;
}
