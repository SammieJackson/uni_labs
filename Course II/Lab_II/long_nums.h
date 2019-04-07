#ifndef LONG_NUMS_H_INCLUDED
#define LONG_NUMS_H_INCLUDED

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
//#include <math.h>
#include <ctype.h>
//#include <algorithm>

using namespace std;

int get_len(const int& a)
{
    int i = 1, b = a;
    while (b >= 10) {
        b = int (floor(b / 10));
        ++i;
    }
    return i;
}

/*
char* multiply_small(const char *num1, const int& len1, const char *num2, const int& len2)
{
    if (len1 < 1 || len2 < 1) throw("\n Invalid array size passed!\n");
    if (len1 > 2 || len2 > 2) throw("\n Too long numbers!\n");
    int n1=0, n2=0, res_i=0;
    for (int i = 0; i < len1; ++i){n1 += pow(10,i) * ( num1[len1 - i] - '0');}
    for (int i = 0; i < len2; ++i){n2 += pow(10,i) * ( num2[len2 - i] - '0');}
    res_i = n1*n2;
    cout<<endl<<res_i;//<<endl<<n1<<endl<<n2;
    int leng = get_len(res_i);
    char* res_c = new char[leng];
    for (int i = 0; i < leng; ++i){res_c[leng-1-i] = res_i % 10; res_i = res_i / 10;}
    return res_c;
} */

class LongNums_0
{
private:
    static const int sys = 10;
    const int len;
    char* num;

public:
    LongNums_0(const int& a);
    LongNums_0(const int& leng, const char* number);
    //LongNums_0& operator *(const LongNums_0& other)const;
    operator string()const;
    LongNums_0& operator +(const LongNums_0& other)const;
    LongNums_0& operator -(const LongNums_0& other)const;
};

LongNums_0::LongNums_0(const int& a):len(get_len(a))
{
    if (a < 0) throw("\n Cannot assign negative value!\n");
    num = new char[len+1];
    num[0] = '+';
    char symb;
    int j = 0;
    int b = a;
    while (b > 9){
        int mod = b % 10;
        symb = static_cast<char> (48 + mod);
        b = (b - mod) / 10;
        num[len - j] = symb;
        ++j;
    }
    symb = static_cast<char> (48 + b);
    num[len - j] = symb;
}

LongNums_0::LongNums_0(const int& leng, const char* number): len(leng)
{
    num = new char[len+1];
    num[0] = '+';
    for (int i = 1; i <= len; ++i){
        //if ( !isdigit(number[i-1]) ) throw("\n Not a number passed as an argument!\n");
        if ( !(number[i-1] > 46 && number[i-1] < 58) ) throw("\n Not a number passed as an argument!\n");
        num[i] = number[i-1];
    }
}

LongNums_0::operator string()const{
    std::ostringstream oss;
    for (int i = 1; i <= len; ++i){
        oss<<this->num[i];
    }
    return oss.str();
}

LongNums_0& LongNums_0::operator +(const LongNums_0& other) const
{
    int perenos = 0, curr_sum = 0, leng = 0;
    char* shorter = this->num;
    char* longer = other.num;
    int short_len = this->len, long_len = other.len;
    if (this->len > other.len) {shorter = other.num; longer = this->num; short_len = other.len; long_len = this->len;}
    //int* sizea = &leng;
    char* res_rev = new char[long_len+1];
    while (leng < short_len){
        curr_sum = (shorter[short_len - leng] - '0') + (longer[long_len - leng] - '0');
        res_rev[long_len - leng] = static_cast<char> (48 + perenos + (curr_sum % sys));
        perenos = ( curr_sum - ( curr_sum % sys ) ) / sys;
        ++leng;
    }
    while (leng < long_len){
        curr_sum = (longer[long_len - leng] - '0') + perenos;
        res_rev[long_len - leng] = static_cast<char> (48 + (curr_sum % sys) );
        perenos = curr_sum - (curr_sum % sys);
        ++leng;
    }
    //while (leng < long_len) {res_rev[long_len - leng] = longer[long_len - leng];}
    if (perenos == 1) {res_rev[0] = '1'; ++leng;} else {
        for (int i = 0; i < leng; ++i) {res_rev[i] = res_rev[i+1]; leng;}
    }
    //char* res_num = new char[leng];
    //for (int i = 0; i <= leng; ++i) {res_num[i] = res_rev[leng-i];}

    LongNums_0 res(leng, res_rev);
    LongNums_0* res_; res_ = &res;
    return (*res_);
}

LongNums_0& multiply_small(const char *num1, const int& len1, const char *num2, const int& len2)
{
    if (len1 < 1 || len2 < 1) throw("\n Invalid array size passed!\n");
    if (len1 > 2 || len2 > 2) throw("\n Too long numbers!\n");
    int n1=0, n2=0, res_i=0;
    for (int i = 0; i < len1; ++i){n1 += pow(10,i) * ( num1[len1 - i] - '0');}
    for (int i = 0; i < len2; ++i){n2 += pow(10,i) * ( num2[len2 - i] - '0');}
    res_i = n1*n2;
    cout<<endl<<res_i;//<<endl<<n1<<endl<<n2;
    int leng = get_len(res_i);
    char* res_c = new char[leng];
    for (int i = 0; i < leng; ++i){res_c[leng-1-i] = res_i % 10; res_i = res_i / 10;}
    LongNums_0 res(leng, res_c);
    LongNums_0* res_; res_ = &res;
    return (*res_);
}

void equalize_length(char *&num1, int& len1, char *&num2, int& len2)
{
    char *longer = num1, *shorter = num2;
    int *long_len, *short_len;
    long_len = &len1; short_len = &len2;
    if (short_len > long_len){longer = num2; shorter = num1; long_len = &len2; short_len = &len1;}
    if ((*long_len) % 2 == 1)
    {
        long_len++;
        for (int i = 0; i < (*long_len); ++i)
        {
            longer[(*long_len) - i] = longer[(*long_len) - i - 1];
        };
        longer[1]='0';
    }
    int short_len0 = (*short_len);
    (*short_len) = (*long_len);
    for (int i = 0; i < short_len0; ++i)
    {
        shorter[(*short_len) - i] = shorter[short_len0 - i];
    }
    for (int i = 1; i < ((*short_len) - (short_len0)); ++i)
    {
        shorter[i] = 0;
    }
}

char karatsuba(const char* num1, const int& len1, char* num2, const int& len2)
{
    char *n1, *n2;
    n1 = num1; n2 = &num2;
    int n1_len = len1; n2_len = len2;
    equalize_length(n1, n1_len, n2, n2_len);
    char *n11, *n12, *n21, *n22;
    int len_n10 = n1_len / 2, len_n20 = n2_len / 2;
    for (int i = 0; i < 1; ++i) {}
    return '0';
}


#endif // LONG_NUMS_H_INCLUDED
