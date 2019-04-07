//Babiienko I. K-11
#include <iostream>
#include "laba5.h"
#include "laba6.h"
#include "laba7.h"
#include "laba8.h"
#include <cstring>
#include "help.h"
#include "copy.h"


using namespace std;

int main()
{
    setlocale(0, "Rus");
    string numb;
    info();
    cout<<"Ця програма виконує в залежності від введених даних одну з лабораторних робіт (5-8)."<<endl;
    cout<<" Лабораторна номер 5:"<<endl;
    info5();
    cout<<endl<<" Лабораторна номер 6:"<<endl;
    info6();
    cout<<" Лабораторна номер 7:"<<endl;
    info7();
    cout<<" Лабораторна номер 8:"<<endl;
    info8();
    cout<<" Для виконання лаби №5 введіть 'laba5'. Аналогічно для інших лабораторних.Для отримання інструкцій введіть 'help'."<<endl;
    cin>>numb; cout<<endl;
    if ("laba5"==numb) laba5(); else
    if ("laba6"==numb) laba6(); else
    if ("laba7"==numb) laba7(); else
    if ("laba8"==numb) laba8(); else
    if ("help"==numb) help(); else
    {cout<<"Ви ввели некоректні дані!"; help();}
    return 0;
}
