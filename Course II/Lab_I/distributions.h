#ifndef DISTRIBUTIONS_H_INCLUDED
#define DISTRIBUTIONS_H_INCLUDED

#include "generators.h"


// отдельно для генератора №7; gen_num1, gen_num2 - номера генераторов 1-4 которые будут использоваться
void print_distribution_0_7(int gen_num1, int gen_num2, int amount, int intervals, int low_bound, int up_bound){
    Gen_7* gen = new Gen_7(gen_num1, gen_num2);
    int* val_arr = new int[intervals];
    double* perc_arr = new double[intervals];
    double* lower_bounds = new double[intervals+1];
    double step = double (up_bound - low_bound) / intervals;
    for (int i = 0; i < intervals+1; ++i){
        lower_bounds[i] = low_bound + i * step;
        if (i != amount) {
            val_arr[i] = 0;
            perc_arr[i] = 0;
        }
    }
    for (int i = 1; i <= amount; ++i)
    {
        pair<double, double> nums = gen->get_nums();
        double k1 = nums.first, k2 = nums.second; //cout<<endl<<k;
        int j = int ( floor( (double) (k1 - low_bound) / step ) );
        val_arr[j] += 1;
        j = int ( floor( (double) (k2 - low_bound) / step ) );
        val_arr[j] += 1;
        //while (k < lower_bounds[9-j]){++j;}
        //val_arr[9-j] += 1;
    }
    std::cout<<"\n Numbers generated - "<<amount<<"\n";
    for (int i = 0; i <= intervals - 1; ++i){
        perc_arr[i] = (double) val_arr[i] / amount;
        std::cout<<"\n   Interval "<<i+1<<" - ["<<lower_bounds[i]<<";"<<lower_bounds[i+1]<<"] - "<<double(perc_arr[i]*100)<<" %"; //val_arr[i] -> perc_arr[i]
    } cout<<endl;
    return;
}

//num - номер генератора; amount - кол-во генерируемых чисел; intervals - кол-во интервалов; low_bound - левый край отрезка; up_bound - правый край;
void print_distribution_general(int num, int amount, int intervals, int low_bound, int up_bound){
    if (low_bound >= up_bound) {throw("\n Invalid bounds for table!\n"); return;}
    if (num < 1 || num > 10) {
        throw("\n Invalid generator number!\n");
        //std::cout<<"\n Invalid generator number!\n";
        return;
    }
    if (amount < 1) {
        throw("\n Negative value!\n");
        //std::cout<<"\n Negative value!\n";
        return;
    }
    Gen_0* gen;
    int a,b;
    switch (num){
    case 1:
        gen = new Gen_1; break;
    case 2:
        gen = new Gen_2; break;
    case 3:
        gen = new Gen_3; break;
    case 4:
        gen = new Gen_4; break;
    case 5:
        cout<<"\n Enter two nums for two generators (#5) (from 1 to 4):";  cin>>a>>b;
        gen = new Gen_5(a,b); break;
    case 6:
        cout<<"\n Enter a num for generator (#6) (from 1 to 4):"; cin>>a;
        gen = new Gen_6(a); break;
    case 7:
        cout<<"\n Enter two nums for two generators (#7) (from 1 to 4):"; cin>>a>>b;
        print_distribution_0_7(a, b, amount, intervals, low_bound, up_bound); return;
    case 8:
        cout<<"\n Enter two nums for two generators (#8) (from 1 to 4):"; cin>>a>>b;
        gen = new Gen_8(a,b); break;
    case 9:
        cout<<"\n Enter a num for generator (#9) (from 1 to 4):"; cin>>a;
        gen = new Gen_9(a); break;
    case 10:
        cout<<"\n Enter two nums for two generators (#10) (from 1 to 4):"; cin>>a>>b;
        gen = new Gen_10(a,b); break;
    }
    int* val_arr = new int[intervals];
    double* perc_arr = new double[intervals];
    double* lower_bounds = new double[intervals+1];
    double step = double (up_bound - low_bound) / intervals;
    for (int i = 0; i < intervals+1; ++i){
        lower_bounds[i] = low_bound + i * step;
        if (i != amount) {
            val_arr[i] = 0;
            perc_arr[i] = 0;
        }
    }
    for (int i = 1; i <= amount; ++i)
    {
        double k = gen->get_num(); //cout<<endl<<k;
        int j = int ( floor( (double) (k - low_bound) / step ) );
        val_arr[j] += 1;
        //while (k < lower_bounds[9-j]){++j;}
        //val_arr[9-j] += 1;
    }
    std::cout<<"\n Numbers generated - "<<amount<<"\n";
    for (int i = 0; i <= intervals - 1; ++i){
        perc_arr[i] = (double) val_arr[i] / amount;
        std::cout<<"\n   Interval "<<i+1<<" - ["<<lower_bounds[i]<<";"<<lower_bounds[i+1]<<"] - "<<double(perc_arr[i]*100)<<" %"; //val_arr[i] -> perc_arr[i]
    } cout<<endl;
}

void print_distribution_rivn(int num, int amount, int intervals){
    if (num < 1 || num > 5) throw("\n Invalid generator number! (1-5)\n");
    print_distribution_general(num, amount, intervals, 0, 1);
}

void print_distribution_norm(int num, int amount, int intervals){
    if (num < 6 || num > 8) throw("\n Invalid generator number! (6-8)\n");
    print_distribution_general(num, amount, intervals, -3, 3);
}

void print_distribution_other(int num, int amount, int intervals){
    if (num < 9 || num > 10) throw("\n Invalid generator number! (9-10)\n");
    print_distribution_general(num, amount, intervals, 0, 100);
}



#endif // DISTRIBUTIONS_H_INCLUDED
