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
    cout<<"�� �������� ������ � ��������� �� �������� ����� ���� � ������������ ���� (5-8)."<<endl;
    cout<<" ����������� ����� 5:"<<endl;
    info5();
    cout<<endl<<" ����������� ����� 6:"<<endl;
    info6();
    cout<<" ����������� ����� 7:"<<endl;
    info7();
    cout<<" ����������� ����� 8:"<<endl;
    info8();
    cout<<" ��� ��������� ���� �5 ������ 'laba5'. ��������� ��� ����� ������������.��� ��������� ���������� ������ 'help'."<<endl;
    cin>>numb; cout<<endl;
    if ("laba5"==numb) laba5(); else
    if ("laba6"==numb) laba6(); else
    if ("laba7"==numb) laba7(); else
    if ("laba8"==numb) laba8(); else
    if ("help"==numb) help(); else
    {cout<<"�� ����� ��������� ���!"; help();}
    return 0;
}
