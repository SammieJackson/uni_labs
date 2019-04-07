#ifndef HELPY_HANDY_H_INCLUDED
#define HELPY_HANDY_H_INCLUDED

// C++ program to find multiplicative modulo inverse using
// Extended Euclid algorithm.
#include<iostream>
using namespace std;

// C function for extended Euclidean Algorithm
//int gcdExtended(int a, int b, int *x, int *y);


// C function for extended Euclidean Algorithm
int gcdExtended(int a, int b, int *x, int *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }

    int x1, y1; // To store results of recursive call
    int gcd = gcdExtended(b%a, a, &x1, &y1);

    // Update x and y using results of recursive
    // call
    *x = y1 - (b/a) * x1;
    *y = x1;

    return gcd;
}

// Function to find modulo inverse of a
void modInverse(int a, int m)
{
    int x, y;
    int g = gcdExtended(a, m, &x, &y);
    if (g != 1)
        cout << "Inverse doesn't exist";
    else
    {
        // m is added to handle negative x
        int res = (x%m + m) % m;
        cout << "Modular multiplicative inverse is " << res;
    }
}

int get_inverse(int a, int m)
{
    int x, y;
    int g = gcdExtended(a, m, &x, &y);
    if (g != 1){
        //cout << "Inverse doesn't exist";
        return 0;
    }
    else
    {
        // m is added to handle negative x
        int res = (x%m + m) % m;
        //cout << "Modular multiplicative inverse is " << res;
        return res;
    }
}

pair<int, double> sum_avrg(int* arr, int sizea){
    if (sizea < 1) {cout<<"\n Array has negative size!\n"; return make_pair(0,0);}
    int sum=0;
    for (int i = 0; i < sizea; ++i) {sum += arr[i];}
    double avr = (double) sum / sizea;
    return make_pair(sum, avr);
}

double dispersion(int* arr, int sizea){
    if (sizea < 1) {cout<<"\n Array has negative size!\n"; return 0;}
    pair<int, int> pairr = sum_avrg(arr, sizea);
    double avg = pairr.second;
    double disp_sum = 0;
    for (int i = 0; i < sizea; ++i){disp_sum += pow((arr[i]-avg), 2);}
    double disp;
    disp = sqrt(disp_sum / sizea);
    return disp;
}

#endif // HELPY_HANDY_H_INCLUDED
