#include <iostream>
#include <vector>

using namespace std;
long long binpowp(long long a, long long k, long long p) {
	if (k == 0) return 1;
	if (k % 2 == 1) return (binpowp(a, k - 1, p) * a) % p;
	else {
		long long b = binpowp(a, k / 2, p) % p;
		return (b * b) % p;
	}
}

long long binpow(long long a, long long k) {
	if (k == 0) return 1;
	if (k % 2 == 1) return binpow(a, k - 1) * a;
	else {
		long long b = binpow(a, k / 2);
		return b * b;
	}
}

int main(){
	long long n, m, k;
	cin >> n >> k >> m;
	struct Pair { long long a; long long b; };
	vector<long long> v1;
	vector<long long> v2;
	vector <Pair> v;
	Pair G;
	if (m == 1) cout << 0 << "\n";
	else{
		if (k != 0 || (n == k)){
			long long temp = 0;
			long long m1 = m;
			for (long long i = 2; i <= m; ++i){
				if (i*i > m1 && m > 1){
					G.a = m;
					G.b = 1;
					v.push_back(G);
					break;
				}
				else{
					if (m%i == 0){
						while (m%i == 0){
							m /= i;
							++temp;
						}
						G.a = i;
						G.b = temp;
						v.push_back(G);
						temp = 0;
					}
				}
			}
			for (long long i = 0; i < v.size(); ++i){
				long long temp = n;
				v2.push_back(0);
				while (temp > 0){
					temp = temp / v[i].a;
					v2[v2.size() - 1] += temp;
				}
				temp = k;
				while (temp > 0){
					temp = temp / v[i].a;
					v2[v2.size() - 1] -= temp;
				}
				temp = n - k;
				while (temp > 0){
					temp = temp / v[i].a;
					v2[v2.size() - 1] -= temp;
				}
			}
			for (long long i = 0; i < v.size(); ++i){
				if (v2[i] >= v[i].b){
					v1.push_back(0);
				}
				else{
					v1.push_back(1);
					long long temp = n;
					long long sum = 1;
					long long x, y, t;
					t = binpow(v[i].a, v[i].b - v2[i]);
					for (long long j = 0; j < k; ++j){
						x = j + 1; y = n - j;
						while (x%v[i].a == 0){
							x /= v[i].a;
						}
						while (y%v[i].a == 0){
							y /= v[i].a;
						}
						v1[v1.size() - 1] = (v1[v1.size() - 1] * (y % t)) % t;
						sum = (sum*x) % t;
					}
					sum = binpowp(sum, (t / (v[i].a))*((v[i].a) - 1) - 1, t);
					v1[v1.size() - 1] = (v1[v1.size() - 1] * sum) % t;
					v1[v1.size() - 1] *= binpow(v[i].a, v2[i]);
				}
			}
			long long t;
			long long result, z = 0, q;
			while (v1[z] == 0){
				++z;
				if (z == v1.size()){
					--z;
					break;
				}
			}
			result = v1[z];
			if (result == 0){
				q = 0;
			}
			else q = binpow(v[z].a, v[z].b);
			for (long long i = 0; i < v2.size(); ++i){
				if (v1[i] != 0){
					t = binpow(v[i].a, v[i].b);
					while ((result%t) != v1[i]){
						result += q;
					}
					if (i != z)	q *= t;
				}
			}
			for (long long i = 0; i < v1.size(); ++i){
				if (v1[i] == 0){
					t = binpow(v[i].a, v[i].b);
					while (result%t != 0){
						result += q;
					}
					q = q*t;
				}
			}
			cout << result << "\n";
		}
		else cout << 1 << "\n";
	}
	system("pause");
	return 0;
}