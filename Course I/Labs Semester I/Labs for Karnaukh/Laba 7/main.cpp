// Babiienko I. K-11
#include "copy.h"
#include "array.h"
#include "maxser.h"
#include <iostream>

using namespace std;

int main(){
setlocale(0, "Rus");
info();
cout<<"Ця програма знаходить довжину найбільшої серії (монотонної послідовності послідовних елементів масиву) введеного масиву цілих чисел. Щоб припинити ввід "<<endl;
cout<<"введіть ctrl+z та натисніть enter"<<endl;
int sizea=0;
const int maxsize=1000;
int a[maxsize];
vvid(a, maxsize, sizea);
if (sizea==0) {cout<<endl<<" Ви ввели порожній массив"<<endl; return 0;}
vyvid(a, sizea);
cout<<endl<<"Його найдовша серія має довжину "<<maxseries(a, sizea);
return 0;
}
