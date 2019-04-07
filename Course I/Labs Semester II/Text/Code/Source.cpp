#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int T;
	cin >> T;
	vector<long long> v;
	for (int i = 0; i < T; ++i)
	{
		int n;
		long long r, m=1;
		cin >> n >> r;
		for (int j = 0; j < n; ++j)
		{
			m *= 2;
		}
		if (r % 2 == 0) cout << "0\n";
		else if (n == 1) cout << "2 0 1\n";
		else
		{
			v.clear();
			if (r % 4 == 1)
			{
				--r;
				while (r != 0)
				{
					v.push_back(r % 2);
					r /= 2;
				}
				v.resize(n + 1);
				for (int j = 0; j < v.size(); ++j)
				{
					r = r * 2 + v[j];
				}
				cout << "2 " << r << " " << m - 1 - r << "\n";
			}
			else
			{
				r = m - r;
				--r;
				while (r != 0)
				{
					v.push_back(r % 2);
					r /= 2;
				}
				v.resize(n + 1);
				for (int j = 0; j < v.size(); ++j)
				{
					r = r * 2 + v[j];
				}
				cout << "2 " << r+1 << " " << m - 2 - r << "\n";
			}
		}
	}
	system("pause");
	return 0;
}