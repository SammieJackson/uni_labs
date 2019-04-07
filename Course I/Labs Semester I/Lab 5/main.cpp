//Babiienko I. K-11
//#include "copy.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include "func5.h"

using namespace std;

int main()
{
    setlocale(0, "Rus");
    //info();
    cout<<"Ця програма табулює значення функцій f(x), S(x) та S(x)-f(x) на відрізку [a; b] з кроком  h, де a0<a, b<b0.";
    cout<<endl<<"f(x)=sh(x), S(x)=sum[0; +infinity](x^(2n+1)/(2n+1)!";
    cout<<endl<<"Kористувач задає:"<<endl<<"– значення a початку відрізку, на якому табулюється функція;"<<endl<<"– значення b кінця відрізку, на якому табулюється функція; (-0.9<=a<b<=0.9)"<<endl<<"– крок h з яким виконується табуляція функції; (h>=0.1)"<<endl<<"- значення e, яке обумовлює точність обчислення";
    const double a0=-0.9, b0=0.9;
    double a, b, h, e, x;
    cout<<endl<<"Введіть a = ";
    cin>>a; if (cin.fail()) {cout<<endl<<"Некоректній ввід!"; return 0;}
    cout<<"Введіть b = ";
    cin>>b; if (cin.fail()) {cout<<endl<<"Некоректній ввід!"; return 0;}
    cout<<"Введіть h = ";
    cin>>h; if (cin.fail()) {cout<<endl<<"Некоректній ввід!"; return 0;}
    cout<<"Введіть e = ";
    cin>>e; if (cin.fail()) {cout<<endl<<"Некоректній ввід!"; return 0;}
    x=a;
    if ((a<a0) || (b>b0) || (a>=b) || (h<0.1)) {cout<<endl<<"Некоректній ввід!"; return 0;}
    vyvid(x, b, h, e);
    return 0;
}

