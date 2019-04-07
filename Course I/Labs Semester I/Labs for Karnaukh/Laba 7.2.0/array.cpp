//Babiienko I. K-11
#include "array.h"
#include <iostream>

using namespace std;

bool vvid(int a[], const int maxsize, int& sizea){
    sizea=0;
    int k;
    while (sizea<maxsize && cin >> k)
        a[sizea++]=k;

    bool rez=1;
    if (sizea<maxsize && !cin.eof()) rez=0;
    else if (sizea==maxsize){
        char c;
        cin >> c;
        if (!cin.eof()) rez=0;
    }
    return rez;
}


void vyvid(const int a[], const int sizea){
cout<<"Ви ввели наступний массив: ";
for (int i=0; i<sizea; i++){cout<<a[i]; if (i==(sizea-1)) cout<<"."; else cout<<", ";}
cout<<endl;
return;
}
