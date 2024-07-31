#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

int n = 11;
int k = 3;
long long kf = 6;
int cycle_types = 56; // for 11 = 56
vector<int> p, cp;
vector<long long> sp;
vector< vector<long long> > tp, m;
long long sum = 0;
int id;
map< vector<int>, int> mp;
bool used[11];
vector<int> s;

inline int get_id(vector<int> s)
{
	if (mp[s] == 0)
		mp[s] = ++id;
	return mp[s];
}

double eps = 1e-7;

int main()
{
	p.clear();
	for (int i = 0; i < n; i++)
		p.push_back(i);
	sp.resize(cycle_types, 0);
	tp.resize(cycle_types, vector<long long> (cycle_types, 0));
	
	do
	{
		int p_id = 0;
		memset(used, 0, sizeof(used));
		s.clear();
		for (int i = 0; i < n; i++)
			if (!used[i])
			{
				int l = 0, k = i;
				while (1)
				{
					l++;
					used[k] = 1;
					k = p[k];
					if (k == i)
						break;
				}
				s.push_back(l);
			}
			sort(s.begin(), s.end());
		p_id = get_id(s);
		sp[p_id - 1]++;

		if (p_id == 1)
		{
			tp[0][0] = kf;												// TODO: check if 1 or not
			continue;
		}
		
		cp = p;
		sort(cp.begin(), cp.begin() + k);
		do
		{
			int cp_id = 0;
			memset(used, 0, sizeof(used));
			s.clear();
			for (int i = 0; i < n; i++)
				if (!used[i])
				{
					int l = 0, k = i;
					while (1)
					{
						l++;
						used[k] = 1;
						k = cp[k];
						if (k == i)
							break;
					}
					s.push_back(l);
				}
				sort(s.begin(), s.end());
			cp_id = get_id(s);
			tp[p_id - 1][cp_id - 1]++;
		}
		while (next_permutation(cp.begin(), cp.begin() + k));
	}
	while (next_permutation(p.begin(), p.end()));

	m.resize(cycle_types, vector<long long> (cycle_types + 1, 0));
	m[0][0] = 1;
	m[0][cycle_types] = 0;
	for (int i = 1; i < cycle_types; i++)
	{
		m[i][i] = sp[i] * kf;
		m[i][cycle_types] = sp[i] * kf;
		for (int j = 0; j < cycle_types; j++)
			m[i][j] -= tp[i][j];
	}

	// Here goes Wolfram!
	freopen("output.txt", "w", stdout);
	printf("m = N[{\n");
	for (int i = 0; i < cycle_types; i++)
	{
		printf("{");
		for (int j = 0; j < cycle_types; j++)
		{
			cout << m[i][j];
			if (j < cycle_types - 1)
				printf(", ");
		}
		if (i < cycle_types - 1)
			printf("},\n");
		else
			printf("}\n");
	}
	printf("}, 50]\n\nb = N[{");
	for (int i = 0; i < cycle_types; i++)
		cout << m[i][cycle_types] << (i < cycle_types - 1 ? ", " : "");
	printf("}, 50]\n\nt = N[{");
	sum = 0;
	for (int i = 0; i < cycle_types; i++)
		sum += sp[i];
	for (int i = 0; i < cycle_types; i++)
		cout << sp[i] << "/" << sum << (i < cycle_types - 1 ? ", " : "");
	cout << "}, 50]\n\n";
	printf("x = LinearSolve[m, b]\n\n");
	printf("x.t\n");
	return 0;
	// ... and here it ends

	return 0;
}