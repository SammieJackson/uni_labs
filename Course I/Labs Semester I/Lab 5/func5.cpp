//Babiienko I. K-11
#include "func5.h"
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

double fx(double x){
 double f;
 f=sinh(x);
 return f;
}

double Sx(double x, double eps){
 double s, t, i;
 i=s=0;
 while ((s-t>=eps) && (i<=n)) {
   t=s;
   s+=(pow(x,2*i+1))/fact(2*i+1);
   i++;
  }
  return s;
}

int fact(int n){
int fact=1;
for (int i=1; i<=n; i++){fact*=i;}
return fact;
}

void vyvid(double x, double b, double h, double e){
    while (x<=b) {
     cout<<endl<<"x = "<<setprecision(3)<<x;
     cout<<endl<<"f(x) = "<<setprecision(3)<<fx(x);
     cout<<endl<<"S(x) = "<<setprecision(3)<<Sx(x, e);
     cout<<endl<<"S(x)-f(x) = "<<setprecision(3)<<Sx(x,e)-fx(x)<<endl;
     x=x+h;
    }
}
