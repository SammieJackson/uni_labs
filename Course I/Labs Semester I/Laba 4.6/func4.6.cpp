//Babiienko I. K-11
#include "func4.6.h"
#include <cmath>

const double e=M_E;

double vyraz(double x){check(x); return tan(5)+e/(x*x);}

void check(double x){if (x==0) throw 1;}
