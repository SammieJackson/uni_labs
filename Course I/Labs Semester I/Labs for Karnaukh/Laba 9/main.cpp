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
     cout<<endl<<" �� �������� ������ � ��������� �� �������� ����� ���� � ������������ ���� (5-8)."<<endl;
     cout<<" ��� ��������� ���� �5 ������ 'laba5'. ��������� ��� ����� ������������.��� ��������� ���������� ������ 'help'."<<endl<<endl;
     if (strcmp(argv[1], "laba5")==0) {cout<<" ����������� ����� 5:"<<endl; info5(); laba5();} else
     if (strcmp(argv[1], "laba6")==0) {cout<<" ����������� ����� 6:"<<endl; info6(); laba6();} else
     if (strcmp(argv[1], "laba7")==0) {cout<<" ����������� ����� 7:"<<endl; info7(); laba7();} else
     if (strcmp(argv[1], "laba8")==0) {cout<<" ����������� ����� 8:"<<endl; info8(); laba8();} else
    {if (strcmp(argv[1], "help")!=0) cout<<"�� ����� ��������� ���!"; help();}
    }
    else if (argc==1) cout<<" �� ������� ����� �������!"; else cout<<endl<<" �������� ���������! ����������� ���!";
    return 0;
}
