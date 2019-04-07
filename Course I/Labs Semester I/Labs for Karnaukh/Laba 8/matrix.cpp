//Babiienko I. K-11
#include "matrix.h"
#include <iostream>

using namespace std;

void create(int a[maxs][maxs], const int sizea){
       int s=1;
   for (int i=0; i<sizea; i++)
   for (int j=0; j<sizea; j++)
   {a[i][j]=s; s++;}
}

void vyvid(const int a[maxs][maxs], const int sizea){
cout<<"Було побудовано матрицу:"<<endl;
for (int i=0; i<sizea; i++){
 cout<<" ";
 for (int j=0; j<sizea; j++){if (a[i][j]<10) cout<<"  "<<a[i][j]<<" ";
  else if ((a[i][j]>9) && (a[i][j]<100)) cout<<" "<<a[i][j]<<" ";
    else cout<<a[i][j]<<" ";
  }
 cout<<endl;
}
}
