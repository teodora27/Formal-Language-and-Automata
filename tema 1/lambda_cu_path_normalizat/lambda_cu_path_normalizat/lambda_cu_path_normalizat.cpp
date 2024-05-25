#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cassert>
#include <map>
using namespace std;
typedef long long ll;
const int N = 10000;
bool vizitat[N][100];
int invers[N];
struct pereche {
	int nod;
	char litera;
};
int n, noduri[N], m, stare_init, nrf, fin[N], nrc;
string s;
vector<vector<pereche>> muchii(N);
int nod1, nod2;
char lit;
int path[10000];
map<int, int> mp;

int dfs(int stare_curenta, int poz, int fin[N], int path[10000], int pozp)
{
	if (vizitat[stare_curenta][poz] == true)
		return false;
	vizitat[stare_curenta][poz] = true;
	//cout << "\n===>starea cuurenta:" << stare_curenta << "  "<<"poz:"<<poz<<" nr:"<<nr;
	if (poz == s.size())
	{
		/*cout << "nrf: " << nrf<<"\n vector final: (";
		for (int i = 1; i <= nrf; i++)
			cout << fin[i] << " ";
		cout << ")";*/
		for (int i = 1; i <= nrf; i++)
		{
			if (stare_curenta == fin[i])
			{
				cout << "drumul: (";
				for (int j = 0; j < pozp; j++)
				{
					cout << invers[path[j]] << " ";/*
					for(auto &stare:mp)
						if(stare.second==path[j])
							cout << stare.first << " ";*/
				}
				cout << invers[stare_curenta];/*
				for (auto& stare : mp)
					if (stare.second == stare_curenta)
						cout << stare.first;*/
				cout << ") ";
				return true;
				break;
			}
		}
		for (int i = 0; i < muchii[stare_curenta].size(); i++)
		{
			if (muchii[stare_curenta][i].litera == '0')
			{
				path[pozp] = stare_curenta;
				if (dfs(muchii[stare_curenta][i].nod, poz, fin, path, pozp + 1))
				{
					return true;
				}
			}
		}

		return false;
	}
	/*cout << "\npozitia " << poz << ":";
	for (int i = 0; i < muchii[stare_curenta].size(); i++)
	{
		if (muchii[stare_curenta][i].litera == s[poz])
		{
			cout << "(" << muchii[stare_curenta][i].litera << " , " << muchii[stare_curenta][i].nod << ")";
		}
	}*/
	for (int i = 0; i < muchii[stare_curenta].size(); i++)
	{
		if (muchii[stare_curenta][i].litera == s[poz])
		{
			path[pozp] = stare_curenta;
			if (dfs(muchii[stare_curenta][i].nod, poz + 1, fin, path, pozp + 1))
			{

				return true;
			}
		}
	}
	for (int i = 0; i < muchii[stare_curenta].size(); i++)
	{
		if (muchii[stare_curenta][i].litera == '0')
		{
			path[pozp] = stare_curenta;

			if (dfs(muchii[stare_curenta][i].nod, poz, fin, path, pozp + 1))
			{
				return true;
			}
		}
	}
	return false;
}
int x;
int main()
{
	cin >> n;
	int numar = 1;
	for (int i = 1; i <= n; i++)
	{
		cin >> x;
		mp[x] = numar;
		numar++;
		noduri[i] = numar;
		invers[i] = x;
		//cin >> noduri[i];
	}
	cin >> m;
	for (int i = 1; i <= m; i++)
	{
		cin >> nod1 >> nod2 >> lit;
		nod1 = mp[nod1];
		nod2 = mp[nod2];
		pereche p;
		p.nod = nod2;
		p.litera = lit;
		muchii[nod1].push_back(p);
	}
	cin >> stare_init;
	stare_init = mp[stare_init];
	cin >> nrf;
	for (int i = 1; i <= nrf; i++)
	{
		//cin >> fin[i];
		cin >> x;
		x = mp[x];
		fin[i] = x;
	}

	cin >> nrc;
	for (int j = 1; j <= nrc; j++)
	{
		cin >> s;
		int pozp = 0;
		cout << "cuvantul " << s << ":";
		if (dfs(stare_init, 0, fin, path, pozp) == true)
			cout << "DA\n";
		else
			cout << "NU\n";
		for (int i = 0; i < N; i++)
			for (int k = 0; k < 100; k++)
				vizitat[i][k] = false;
	}
	
	return 0;
}

/*
4
1 2 3 5
8
2 2 0
1 2 a
1 5 b
5 1 0
5 2 b
2 3 0
3 5 b
5 3 0
1
1
5
5
bb
ab
bbbbbb
aab
bbab



4
1 2 3 4
7
1 1 b
1 2 a
1 4 a
2 4 b
2 3 b
4 4 a
4 3 a
1
1
3
5
bbab
aaaaa
abb
abab
aa


*/
