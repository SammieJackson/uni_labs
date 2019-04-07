//Babiienko I. K-11
#include "func5.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include "vyvid.h"

using namespace std;

void vyvid(double x, const double b, const double h, const double e){
     cout<<fixed<<endl<<"x = "<<setprecision(kolvoznakov)<<x;
     cout<<fixed<<endl<<"f(x) = "<<setprecision(kolvoznakov)<<fx(x);
     cout<<fixed<<endl<<"S(x) = "<<setprecision(kolvoznakov)<<Sx(x, e);
     cout<<fixed<<endl<<"S(x)-f(x) = "<<setprecision(2*kolvoznakov)<<Sx(x,e)-fx(x)<<endl;
}

void allvyvid(double x, const double b, const double h, const double e){
    while (x<=b) {
        vyvid(x, b, h, e);
        x += h;
    }
}
