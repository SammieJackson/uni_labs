#ifndef GENERATORS_H_INCLUDED
#define GENERATORS_H_INCLUDED

//#define _USE_MATH_DEFINES

#include <cmath>
//#include <math.h>
#include <stdlib.h>
#include <iomanip>
#include "helpy_handy.h"



const double Eulersconst = std::exp(1.0);
const double Pi = 1;


class Gen_0{
public:
    virtual int get_int_num();
    virtual double get_num();
};

int Gen_0::get_int_num(){
    return 0;
}

double Gen_0::get_num(){
    return this->get_int_num();
}

class Gen_1: public Gen_0
{
//private:
public:
    const int m_1 = 101, a_1 = 43, c_1 = 42;
    int gen_1_count = 0, x_1;
    double u_1;

public:
    int get_int_num() override;
    double get_num()override;
};

int Gen_1::get_int_num(){
    if (gen_1_count == 0) {gen_1_count++; x_1 = rand() % m_1; u_1 = (double) x_1 / m_1; return x_1;}
    x_1 = (a_1 * x_1 + c_1) % m_1;
    gen_1_count++;
    u_1 = (double) x_1 / m_1;
    return x_1;
}

double Gen_1::get_num(){
    this->get_int_num();
    return u_1;
}

class Gen_2: public Gen_0
{
private:
    const int m_2 = 101, d_2 = 246, a_2 = 123, c_2 = 43;
    int gen_2_count = 0, x_2;
    double u_2;

public:
    int get_int_num() override;
    double get_num()override;
};

int Gen_2::get_int_num(){
    if (gen_2_count == 0) {gen_2_count++; x_2 = rand() % m_2; u_2 = (double) x_2 / m_2; return x_2;}
    x_2 = ( ((d_2 * ((d_2 * x_2) % m_2)) % m_2) + ((a_2 * x_2 + c_2) % m_2) ) % m_2;
    gen_2_count++;
    u_2 = (double) x_2 / m_2;
    return x_2;
}

double Gen_2::get_num(){
    this->get_int_num();
    return u_2;
}

class Gen_3: public Gen_0
{
private:
    const int m_3 = 1000;
    int x_30, x_31, x_32, gen_3_count = 0;
    double u_3;

public:
    int get_int_num() override;
    double get_num()override;
};

int Gen_3::get_int_num(){
    if (gen_3_count == 0) {
        x_30 = rand() % m_3;
        x_31 = rand() % m_3;
        x_32 = (x_30 + x_31) % m_3;
        ++gen_3_count;
        u_3 = (double) x_30 / m_3;
        return x_30;
    } else
    if (gen_3_count == 1) {++gen_3_count; u_3 = (double) x_31 / m_3; return x_31;} else
    if (gen_3_count == 2) {++gen_3_count; u_3 = (double) x_32 / m_3; return x_32;} else {
        x_30 = x_31;
        x_31 = x_32;
        x_32 = (x_30 + x_31) % m_3;
    }
    u_3 = (double) x_32 / m_3;
    return x_32;
}

double Gen_3::get_num(){
    this->get_int_num();
    return u_3;
}

class Gen_4: public Gen_0
{
private:
    const int m_4 = 101, a_4 = 43, c_4 = 42;
    int x_4, gen_4_count = 0;
    double u_4;

public:
    int get_int_num() override;
    double get_num() override;
};

int Gen_4::get_int_num(){
    if (gen_4_count == 0) {gen_4_count++; x_4 = rand() % m_4; u_4 = (double) x_4 / m_4; return x_4;}
    int i = get_inverse(x_4, m_4);
    if (i == 0) x_4 = (a_4 * x_4 + c_4) % m_4; else
    x_4 = (a_4 * i + c_4) % m_4;
    gen_4_count++;
    u_4 = (double) x_4 / m_4;
    return x_4;
}

double Gen_4::get_num(){
    this->get_int_num();
    return u_4;
}

class Gen_5: public Gen_0
{
private:
    Gen_0* gen1;
    Gen_0* gen2;
    const int m_5 = 101;
    int x_5, y_5, z_5, gen_5_count = 0;
    double u_5;

public:
    Gen_5(int a, int b);
    int get_int_num() override;
    double get_num() override;
};

Gen_5::Gen_5(int a, int b){
    if (a == b || a<1 || a>4 || b<1 || b>4){gen1 = new Gen_1; gen2 = new Gen_2; return;}
    switch (a){
    case 1:
        gen1 = new Gen_1; break;
    case 2:
        gen1 = new Gen_2; break;
    case 3:
        gen1 = new Gen_3; break;
    case 4:
        gen1 = new Gen_4; break;
    }
    switch (b){
    case 1:
        gen2 = new Gen_1; break;
    case 2:
        gen2 = new Gen_2; break;
    case 3:
        gen2 = new Gen_3; break;
    case 4:
        gen2 = new Gen_4; break;
    }
}

int Gen_5::get_int_num(){
    x_5 = gen1->get_int_num();
    y_5 = gen2->get_int_num();
    z_5 = (x_5 - y_5 + m_5) % m_5;
    u_5 = (double) z_5 / m_5;
    gen_5_count++;
    return z_5;
}

double Gen_5::get_num(){
    this->get_int_num();
    return u_5;
}


class Gen_6:public Gen_0
{
private:
    Gen_0* gen;
    double x_6, m = 0, sigma = 1;

public:
    Gen_6(int a);
    double get_num() override;
};

Gen_6::Gen_6(int a){
    if (a<1 || a>4){gen = new Gen_1; return;}
    switch (a){
    case 1:
        gen = new Gen_1; break;
    case 2:
        gen = new Gen_2; break;
    case 3:
        gen = new Gen_3; break;
    case 4:
        gen = new Gen_4; break;
    }
}

double Gen_6::get_num(){
    double current_sum = 0;
    for (int i = 1; i < 13; ++i){current_sum += gen->get_num();}
    x_6 = m + (current_sum - 6) * sigma;
    return x_6;
}

class Gen_7: public Gen_0
{
private:
    double x7_1, x7_2;
    Gen_0* gen1;
    Gen_0* gen2;

public:
    Gen_7(int a, int b);
    pair<double, double> get_nums();
};

Gen_7::Gen_7(int a, int b){
    if (a == b || a<1 || a>4 || b<1 || b>4){gen1 = new Gen_1; gen2 = new Gen_2; return;}
    switch (a){
    case 1:
        gen1 = new Gen_1; break;
    case 2:
        gen1 = new Gen_2; break;
    case 3:
        gen1 = new Gen_3; break;
    case 4:
        gen1 = new Gen_4; break;
    }
    switch (b){
    case 1:
        gen2 = new Gen_1; break;
    case 2:
        gen2 = new Gen_2; break;
    case 3:
        gen2 = new Gen_3; break;
    case 4:
        gen2 = new Gen_4; break;
    }
}

pair<double, double> Gen_7::get_nums(){
     double u1, u2, v1, v2, s;
     do {
        u1 = gen1->get_num(); u2 = gen2->get_num();
        v1 = 2*u1 - 1; v2 = 2*u2 - 1;
        s = (pow(v1,2)+pow(v2,2));
     } while (s >= 1);
     double v0 = sqrt( ( (-2) * log(s) ) / s );
     x7_1 = v1 * v0;
     x7_2 = v2 * v0;
     return make_pair(x7_1, x7_2);
}

class Gen_8: public Gen_0
{
private:
    Gen_0* gen1;
    Gen_0* gen2;
    double x_8;

public:
    Gen_8(int a, int b);
    double get_num() override;
};

Gen_8::Gen_8(int a, int b){
    if (a == b || a<1 || a>4 || b<1 || b>4){gen1 = new Gen_1; gen2 = new Gen_2; return;}
    switch (a){
    case 1:
        gen1 = new Gen_1; break;
    case 2:
        gen1 = new Gen_2; break;
    case 3:
        gen1 = new Gen_3; break;
    case 4:
        gen1 = new Gen_4; break;
    }
    switch (b){
    case 1:
        gen2 = new Gen_1; break;
    case 2:
        gen2 = new Gen_2; break;
    case 3:
        gen2 = new Gen_3; break;
    case 4:
        gen2 = new Gen_4; break;
    }
}

double Gen_8::get_num(){
    bool flag=1;
    do {
        double u = gen1->get_num(), v = gen2->get_num();
        if (u == 0) u = (double) rand() / RAND_MAX;
        x_8 = sqrt(8 / Eulersconst) * (v-0.5) / u;
        double x_sqr = pow(x_8,2);
        double up_check = 5 - ( 4 * u * pow(Eulersconst, 0.25) );
        double low_check = 1.4 + ( ( 4 * pow(Eulersconst, -1.35) ) / u );
        double final_check = (-4) * log(u);
        if (x_sqr <= up_check) flag = 0; else
        if (x_sqr < low_check) flag = 0; else
        if (x_sqr <= final_check) flag = 0;
    } while (flag);
    return x_8;
}

class Gen_9: public Gen_0
{
private:
    double x_9;
    const double myu = 1;
    Gen_0* gen;

public:
    Gen_9(int a);
    double get_num() override;
};

Gen_9::Gen_9(int a){
    if (a<1 || a>4){gen = new Gen_1; return;}
    switch (a){
    case 1:
        gen = new Gen_1; break;
    case 2:
        gen = new Gen_2; break;
    case 3:
        gen = new Gen_3; break;
    case 4:
        gen = new Gen_4; break;
    }
}

double Gen_9::get_num(){
    double u = gen->get_num();
    x_9 = (-myu) * log(u);
    return x_9;
}

class Gen_10: public Gen_0
{
private:
    double x_10;
    const double a = 2;
    Gen_0* gen1;
    Gen_0* gen2;

public:
    Gen_10(int a, int b);
    double get_num() override;
};

Gen_10::Gen_10(int a, int b){
    if (a == b || a<1 || a>4 || b<1 || b>4){gen1 = new Gen_1; gen2 = new Gen_2; return;}
    switch (a){
    case 1:
        gen1 = new Gen_1; break;
    case 2:
        gen1 = new Gen_2; break;
    case 3:
        gen1 = new Gen_3; break;
    case 4:
        gen1 = new Gen_4; break;
    }
    switch (b){
    case 1:
        gen2 = new Gen_1; break;
    case 2:
        gen2 = new Gen_2; break;
    case 3:
        gen2 = new Gen_3; break;
    case 4:
        gen2 = new Gen_4; break;
    }
}

double Gen_10::get_num(){
    double u, x; bool flag = 1;
    do {
        u = gen1->get_num();
        double y = tan(u * Pi);
        x = a - 1 + ( y * sqrt( 2 * a - 1 ) );
        if (x > 0) {
            double v = gen2->get_num();
            double check = ( 1 + pow(y, 2) ) * ( exp( (a - 1) * log(x / (a - 1)) - y * sqrt(2 * a - 1) ) );
            if (v <= check) flag = 0;
        }
    } while (flag);
    return x_10;
}

#endif // GENERATORS_H_INCLUDED
