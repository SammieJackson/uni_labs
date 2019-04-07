//Babiienko I. K-11
#include "func5.h"
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

double fx(const double x){
 double f;
 f=sinh(x);
 return f;
}

double Sx(const double x, const double eps){
 double s, t=1, i;
 i=s=0;
 while ((abs(s-t)>=eps) && (i<=suma)) {
   t=s;
   s+=(pow(x,2*i+1))/fact(2*i+1);
   i++;
  }
  return s;
}

int fact(const int n){
int fact=1;
for (int i=1; i<=n; i++){fact*=i;}
return fact;
}
