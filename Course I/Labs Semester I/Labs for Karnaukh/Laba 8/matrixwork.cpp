//Babiineko I. K-11
#include "matrix.h"
#include "matrixwork.h"

int suma(const int a[maxs][maxs], const int sizea){
int sumam=0, up=0, down=sizea-1, j=sizea-1, i;
while (down>=up) {
for (i=up; i<=down; i++){sumam+=a[i][j];}
j--;
down--;
up++;
}
return sumam;
}
