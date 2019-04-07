#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <cmath>
#include <stdlib.h>
#include <iomanip>
#include "helpy_handy.h"

using namespace std;

const int m_1 = 101, a_1 = 43, c_1 = 42;
int gen_1_count = 0, x_1;
double u_1;

int get_num_1(){
    if (gen_1_count == 0) {gen_1_count++; x_1 = rand() % m_1; u_1 = (double) x_1 / m_1; return x_1;}
    x_1 = (a_1 * x_1 + c_1) % m_1;
    gen_1_count++;
    u_1 = (double) x_1 / m_1;
    return x_1;
}

double get_01_num_1(){
    get_num_1();
    return u_1;
}

/////////////////////////////////////////////////////////////////////////////

const int m_2 = 101, d_2 = 246, a_2 = 123, c_2 = 43;
int gen_2_count = 0, x_2;
double u_2;

int get_num_2(){
    if (gen_2_count == 0) {gen_2_count++; x_2 = rand() % m_2; u_2 = (double) x_2 / m_2; return x_2;}
    x_2 = ( ((d_2 * ((d_2 * x_2) % m_2)) % m_2) + ((a_2 * x_2 + c_2) % m_2) ) % m_2;
    gen_2_count++;
    u_2 = (double) x_2 / m_2;
    return x_2;
}

double get_01_num_2(){
    get_num_2();
    return u_2;
}

////////////////////////////////////////////////////////////////////////////////

const int m_3 = 1000;
int x_30, x_31, x_32, gen_3_count = 0;
double u_3;

int get_num_3(){
    if (gen_3_count == 0) {
        x_30 = rand() % m_3;
        x_31 = rand() % m_3;
        x_32 = (x_30 + x_31) % m_3;
        ++gen_3_count;
        u_3 = x_30 / m_3;
        return x_30;
    } else
    if (gen_3_count == 1) {++gen_3_count; u_3 = x_31 / m_3; return x_31;} else
    if (gen_3_count == 2) {++gen_3_count; u_3 = x_32 / m_3; return x_32;} else {
        x_30 = x_31;
        x_31 = x_32;
        x_32 = (x_30 + x_31) % m_3;
    }
    u_3 = x_32 / m_3;
    return x_32;
}

double get_01_num_3(){
    get_num_3();
    return u_3;
}
///////////////////////////////////////////////////////////////////////////////

const int m_4 = 101, a_4 = 43, c_4 = 42;
int x_4, gen_4_count = 0;
double u_4;

int get_num_4(){
    if (gen_4_count == 0) {gen_4_count++; x_4 = rand() % m_4; u_4 = x_4 / m_4; return x_4;}
    int i = get_inverse(x_4, m_4);
    if (i == 0) x_4 = (a_4 * x_4 + c_4) % m_4; else
    x_4 = (a_4 * i + c_4) % m_4;
    gen_4_count++;
    u_4 = x_4 / m_4;
    return x_4;
}

double get_01_num_4(){
    get_num_4();
    return u_4;
}
/////////////////////////////////////////////////////////////////////////////////////

void print_distribution_14(int num, int amount){
    if (num < 1 || num > 4) {
        throw("\n Invalid generator number!\n");
        //std::cout<<"\n Invalid generator number!\n";
        return;
    }
    if (amount < 1) {
        throw("\n Negative value!\n");
        //std::cout<<"\n Negative value!\n";
        return;
    }

    int* val_arr = new int[10];
    double* perc_arr = new double[10];
    double* lower_bounds = new double[11];
    for (int i = 0; i < 11; ++i){
        lower_bounds[i] = i * 0.1;
        if (i != 10) {
            val_arr[i] = 0;
            perc_arr[i] = 0;
        }
    }
    for (int i = 1; i <= amount; ++i)
    {
        double k = get_01_num_1(); cout<<endl<<k;
        int j = 0;
        while (k < lower_bounds[9-j]){++j;}
        val_arr[9-j] += 1;
    }
    std::cout<<"\n Numbers generated - "<<amount<<"\n";
    for (int i = 0; i <= 9; ++i){
        perc_arr[i] = val_arr[i] / amount;
        std::cout<<"\n   Interval "<<i+1<<" - ["<<lower_bounds[i]<<";"<<lower_bounds[i+1]<<"] - "<<val_arr[i]<<" "; //val_arr[i] -> perc_arr[i]
    }
}

#endif // FUNCTIONS_H_INCLUDED
