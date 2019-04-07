//Babiienko I. K-11
//#include "copy.h"
#include "array.h"
#include <iostream>

using namespace std;

int main(){
setlocale(0, "Rus");
//info();
cout<<"÷€ програма знаходить значенн€ найменшого нев≥д'Їмного елемента введеного масива ц≥лих чисел. ўоб завершити введенн€ масиву введ≥ть ctrl+z та натисн≥ть enter."<<endl;
int sizea=0;
const int maxsize=1000;
int a[maxsize];
vvid(a, maxsize, sizea);
if (sizea==0) {cout<<endl<<"¬и ввели порожн≥й массив"; return 0;}
vyvid(a, sizea);
cout<<"…ого найменший невiд'Їмний елемент рiвний "<<mini(a, sizea);
return 0;
}
