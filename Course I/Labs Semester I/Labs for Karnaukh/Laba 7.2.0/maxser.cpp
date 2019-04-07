//Babiienko I. K-11
#include "maxser.h"

int maxseries(const int a[], const int sizea){
int serless=1, serbig=1, maxs=1;
for (int i=1; i<sizea; i++){
 if (a[i-1]==a[i]) {serless++; serbig++;} else
 if (a[i-1]<a[i]) {serbig++; serless=1;} else
 if (a[i-1]>a[i]) {serless++; serbig=1;}
 if (maxs<serbig) maxs=serbig;
 if (maxs<serless) maxs=serless;
}
return maxs;
}
