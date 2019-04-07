//Babiienko I. K-11
#include "matrix.h"
#include <iostream>

using namespace std;

int create(int a[maxs][maxs], int sizea){
       int s=1;
   for (int i=0; i<sizea; i++)
   for (int j=0; j<sizea; j++)
   {a[i][j]=s; s++;}
return 0;
}

int vyvid(const int a[maxs][maxs], int sizea){
cout<<"Було побудовано матрицу:"<<endl;
for (int i=0; i<sizea; i++){
 for (int j=0; j<sizea; j++){if (a[i][j]<10) cout<<" "<<a[i][j]<<" "; else cout<<a[i][j]<<" ";}
 cout<<endl;
}
return 0;
}

int suma(const int a[maxs][maxs], int sizea){
int sumam=0, up=0, down=sizea-1, j=sizea-1, i;
while (down>=up) {
for (i=up; i<=down; i++){sumam+=a[i][j];}
j--;
down--;
up++;
}
return sumam;
}
