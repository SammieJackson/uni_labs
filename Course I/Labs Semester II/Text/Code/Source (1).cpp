#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
ifstream in;
ofstream out;

int main()
{
	in.open("A-small-attempt0.in");
	out.open("output.txt");
	out << fixed;
	out.precision(10);
	int T;
	in >> T;
	const long double pi = 3.141592653589793238462643;
	for (int i = 0; i < T; ++i)
	{
		out << "Case #" << i + 1 << ": ";
		int N, K;
		long double temp;
		vector<long double> vR, vH;
		in >> N >> K;
		pair<long double, int> maxS1, maxS2;
		maxS1.first = 0, maxS2.first = 0;
		vector< pair <long double, int > > v;
		for (int j = 0; j < N; ++j)
		{
			in >> temp;
			vR.push_back(temp);
			in >> temp;
			vH.push_back(temp);
			temp = 2*vH[j] * vR[j];
			v.push_back({ temp, j });
			if (maxS1.first < temp) maxS1 = { temp, j };
			if (maxS2.first < vR[j]) maxS2 = { vR[j], j };
		}
		sort(v.begin(), v.begin() + N);
		long double sum = 0;
		long double max = 0;
		bool b = true;
		long double ris;
		int temp1;
		temp1 = v.size()-1;
		int num=-1;
		ris = maxS2.first*maxS2.first - vR[v[temp1].second] * vR[v[temp1].second]+v[maxS2.second].first;
		long double mem = vR[v[temp1].second] * vR[v[temp1].second];
		pair<long double, int> max1;
		max1.first = 0;
		long double check = 0;
		for (int j = temp1; j > -1; --j)
		{
			if (j > temp1 - K)
			{
				sum = sum + v[j].first;
				if (max1.first < vR[v[j].second])
				{
					max1 = { vR[v[j].second], v[j].second };
					check = max1.first*max1.first + 2 * max1.first*vH[max1.second];
				}
				if (v[j].second == maxS2.second) b = !b;
				else
					if (ris > v[j].first)
					{
						if (num != -1)
						{
							if (v[j].first < v[num].first) num = j;
						}
						else num = j;
					}
			}
			else
			{
				if (check < v[j].first + 2 * vR[v[j].second] * vH[v[j].second]) check = v[j].first + 2 * vR[v[j].second] * vH[v[j].second];
			}
		}
		if (!b || num==-1)
		{
			sum = sum + max1.first*max1.first;
			sum = sum*pi;
			out << sum << "\n";
		}
		else
		{
			sum = sum + check - 2 * max1.first*vH[max1.second];
			sum = pi*sum;
			out << sum << "\n";
		}
	}
	in.close();
	out.close();
	return 0;
}
