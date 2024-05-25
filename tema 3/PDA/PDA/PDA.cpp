#include <iostream>
#include <cassert>
#include <vector>

using namespace std;
/*
Se considera:
Q, the set of states -> 0,1,2,...,nrStari-1
∑, the set of input symbols -> a,b,c,...,z
Γ, the set of pushdown symbols -> A,B,C,...,Z
Z, the initial pushdown symbol -> Z
*/


/*
Pt o tranzitie se cisteste astfel:
stare 
stare
litera
ce se scoate
ce se pune
*/

class PDA {
    int nrStari;
    int stare_init;
    vector<bool>finale;
    int nrTranzitii;
    vector<vector<vector<vector<pair<string, string>>>>>tranzitii;


public:
    friend istream& operator>>(istream& in, PDA& a) {
        in >> a.nrStari;
        a.finale.resize(a.nrStari);
        a.tranzitii.resize(a.nrStari, vector<vector<vector<pair<string, string>>>>(a.nrStari, vector<vector<pair<string, string>>>(27)));
        in >> a.stare_init;
        int nrFinale;
        in >> nrFinale;
        for (int i = 0; i < nrFinale; i++) {
            int x;
            in >> x;
            a.finale[x] = true;
        }
        in >> a.nrTranzitii;
        for (int i = 0; i < a.nrTranzitii; i++) {
            int s1, s2;
            char lit;
            string scoate, pune;
            cin >> s1 >> s2 >> lit >> scoate >> pune;
            if(lit!='0')
                a.tranzitii[s1][s2][lit - 'a'].push_back( { scoate,pune });
            else
                a.tranzitii[s1][s2][26].push_back( { scoate,pune });
        }     
        return in;
    }
    friend ostream& operator<<(ostream& out, PDA& a) {
        out << "Numarul de stari este: " << a.nrStari << "\n";
        out << "Starea initiala este: " << a.stare_init << "\n";
        out << "Starile finale sunt: ";
        for (int i = 0; i < a.finale.size(); i++)
            if (a.finale[i] == true)
                out << i << " ";
        out << "\nTranzitiile sunt:\n";
        for (int i = 0;i < a.tranzitii.size(); i++) {
            for (int j = 0;j < a.tranzitii[i].size(); j++) {
                for (int k = 0; k < 27; k++) {
                    if (a.tranzitii[i][j][k].size()!=0) {
                        for(int st=0;st<a.tranzitii[i][j][k].size();st++)
                            out << "starea " << i << " starea " << j << " litera " <<char( k + 'a') << " scoate " << a.tranzitii[i][j][k][st].first << " pune " << a.tranzitii[i][j][k][st].second << "\n";
                    }
                }
            }
        }
        return out;
    }

   bool apartine(string s) {
    string stiva;
    stiva += 'Z';
    int stareCurenta = stare_init;
    for (int poz = 0; poz < s.size(); poz++)
    {
        if (stiva == "")
        {
            return false;
        }
        char lit = s[poz];
        char litera = 26;
        string ulimStiva(1, stiva[stiva.size() - 1]);
        bool gasit = false;
       /* cout <<"-------------------------------------- " << "\n";
        cout <<"litera curenta " << lit << "\n";*/
        for (int nextStare = 0; nextStare < nrStari; nextStare++)
        {      
                //cout << "starea urm " << nextStare << "\n";
                assert(lit - 'a' >= 0 && lit - 'a' < 26 && lit != '0' && lit - 'a' < tranzitii[stareCurenta][nextStare].size());
                for (int i = 0; i < tranzitii[stareCurenta][nextStare][lit - 'a'].size(); i++)
                {
                    if (tranzitii[stareCurenta][nextStare][lit - 'a'][i].first == ulimStiva) {
                       /* cout << "starea urm " << nextStare << "\n";
                        cout << "stiva " << stiva << "\n";*/
                        gasit = true;
                        stiva.pop_back();
                        if (tranzitii[stareCurenta][nextStare][lit - 'a'][i].second != "0")
                        {
                            string cuv = tranzitii[stareCurenta][nextStare][lit - 'a'][i].second;
                            reverse(cuv.begin(), cuv.end());
                            stiva +=cuv;
                        }
                        stareCurenta = nextStare;
                        //cout << "stiva " << stiva << "\n";
                    }
                    
                }
            
        }
        if (gasit == false)
            return false;
    }
   /* cout << stiva << "\n"<<( stiva == "")<<"\n";
    cout << "starea curenta " << stareCurenta << "\n";*/
    
     if (stiva == ""||finale[stareCurenta])
            return true;
    
    return false;
}
};

int main()
{
    FILE* filePtr;
    freopen_s(&filePtr, "input.txt", "r", stdin);
    PDA p;
    cin >> p;
    //cout << p;
    string s;
    cin >> s;
    //cout << s;
    if (p.apartine(s))
        cout << "Cuvantul apartine\n";
    else
        cout << "Cuvantul nu apartine\n";


}
