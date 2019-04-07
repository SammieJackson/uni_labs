//Babiienko I. K-11
#include "miniel.h"

int mini(const int a[], const int sizea){
int mini=a[0];
for (int i=0; i<sizea; i++){if ((a[i]>=0) && (mini>a[i])) mini=a[i];}
return mini;
}
