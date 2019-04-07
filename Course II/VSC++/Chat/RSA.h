#ifndef RSA_H_INCLUDED
#define RSA_H_INCLUDED

#include <string>
#include <vector>

using namespace std;

long long binpowM(long long a, long long n, long long m);
long long gcd(long long a, long long b, long long & x, long long & y);
long long reverse(long long fi, long long e);
void encode(vector<long long>& v, long long e, long long n);
void decode(vector<long long>& v, long long d, long long n);
void read(vector<long long>& v);
void output(vector<long long>& v);


string encrypt_string(string msg);
string decrypt_string(string msg);
//char* encrypt_string_c(char* msg);
//char* decrypt_string_c(char* msg);

#endif // RSA_H_INCLUDED
