#include <iostream>
#include <string>
#include <map>
using namespace std;
typedef long long ll;
int noduri[100];
int mat[100][27];
int n, m, i;
int nrcuv;
string s;
map<int, int> mp;
int main()
{
	cin >> n;		
	int numar = 1;				
	for (i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		mp[x] = numar;
		numar++;
		noduri[i] = mp[x];
	}
	cin >> m;	
	
	for (i = 1; i <= m; i++)
	{
		int nod1, nod2;
		
		char caracter;
		cin >> nod1 >> nod2;
		nod1 = mp[nod1];
		nod2 = mp[nod2];
		cin >> caracter;
		mat[nod1][caracter - 'a' + 1] = nod2;
	}
	
	int stare_init;
	cin >> stare_init;
	stare_init = mp[stare_init];
	int nrf;
	cin >> nrf;
	int fin[100];
	for (i = 1; i <= nrf; i++)
	{
		int x;
		cin >> x;
		fin[i] = mp[x];
		
	}
	cin >> nrcuv;
	int path[10000];
	for (i = 1; i <= nrcuv; i++)
	{
		cin >> s;
		cout << "cuvantul " << s << ":";
		int stare_curenta = stare_init;
		int poz = 0;
		int am_afisat = 0;
		while (poz < s.size())
		{
			
			//cout << "stare curenta:" << stare_curenta << "   litera: " << s[poz];
			if (mat[stare_curenta][s[poz]-'a'+1] == 0)
			{
				cout << "NU\n";
				am_afisat = 1;
				break;
			}
			path[poz] = stare_curenta;
			stare_curenta = mat[stare_curenta][s[poz] - 'a' + 1];
			poz++;
		}
		if (am_afisat == 0)
		{
			int ok = 0;
			for (int j = 1; j <= nrf; j++)
				if (fin[j] == stare_curenta)
				{
					path[poz] = stare_curenta;
					ok = 1;
					cout << "DA\n";
					cout << "drumul (";
					for (int k = 0; k <= poz; k++)
					{
						for (auto& stare : mp)
							if (stare.second == path[k])
								cout << stare.first << " ";
					}
					cout << ")\n";
					break;
				}
			if (ok == 0)
				cout << "NU\n";
		}
	}
	return 0;
}

/*
3
1 2 3
6
1 1 a
1 2 b
1 3 c
2 2 b
2 3 c
3 3 c
1
3
1 2 3
5
aaabc
bac
a
bab
aabc
*/
