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

int main(int argc, char* argv[])
{
    setlocale(0, "Rus");
    cout<<endl;
    info();
    if (argc==2) {
     cout<<endl<<" Ця програма виконує в залежності від введених даних одну з лабораторних робіт (5-8)."<<endl;
     cout<<" Для виконання лаби №5 введіть 'laba5'. Аналогічно для інших лабораторних.Для отримання інструкцій введіть 'help'."<<endl<<endl;
     if (strcmp(argv[1], "laba5")==0) {cout<<" Лабораторна номер 5:"<<endl; info5(); laba5();} else
     if (strcmp(argv[1], "laba6")==0) {cout<<" Лабораторна номер 6:"<<endl; info6(); laba6();} else
     if (strcmp(argv[1], "laba7")==0) {cout<<" Лабораторна номер 7:"<<endl; info7(); laba7();} else
     if (strcmp(argv[1], "laba8")==0) {cout<<" Лабораторна номер 8:"<<endl; info8(); laba8();} else
    {if (strcmp(argv[1], "help")!=0) cout<<"Ви ввели некоректні дані!"; help();}
    }
    else if (argc==1) cout<<" Не введено жодної команди!"; else cout<<endl<<" Забагато аргументів! Некоректний ввід!";
    return 0;
}
