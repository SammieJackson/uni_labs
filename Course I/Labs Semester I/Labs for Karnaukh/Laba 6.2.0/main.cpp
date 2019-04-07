//Babiienko I. K-11
#include "copy.h"
#include "array.h"
#include "miniel.h"
#include <iostream>

using namespace std;

int main(){
setlocale(0, "Rus");
info();
cout<<"Ця програма знаходить значення найменшого невід'ємного елемента введеного масива цілих чисел. Щоб завершити введення масиву введіть ctrl+z та натисніть enter."<<endl;
int sizea=0;
const int maxsize=1000;
int a[maxsize];
cout<<"Введіть массив поелементно через space: "<<endl;
if (!vvid(a, maxsize, sizea)){ cout << "Помилка при введеннi" << endl; return 0;}
if (sizea==0) {cout<<endl<<"Ви ввели порожній массив"; return 0;}
vyvid(a, sizea);
cout<<"Його найменший невiд'ємний елемент рiвний "<<mini(a, sizea);
return 0;
}
