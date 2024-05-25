#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

/*
Se considera alfabetul de intrare a,b,...z
*/

class Transducer {
    int nrStari;
    int stare_init;
    vector<bool>finale;
    int nrTranzitii;
    vector<vector<vector<string>>>tranzitii;


public:
    friend istream& operator>>(istream& in, Transducer& a) {
        in >> a.nrStari;
        a.finale.resize(a.nrStari);
        a.tranzitii.resize(a.nrStari, vector<vector<string>>(a.nrStari, vector<string>(26,"")));
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
            int st1, st2;
            char lit;
            string pune;
            in >> st1 >> st2 >> lit >> pune;
            assert(lit <= 'z' && lit >= 'a');
            a.tranzitii[st1][st2][lit - 'a'] =pune;

        }
        return in;
    }
    friend ostream& operator<<(ostream& out, Transducer& a) {
        out << "Numarul de stari este: " << a.nrStari << "\n";
        out << "Starea initiala este: " << a.stare_init << "\n";
        out << "Starile finale sunt: ";
        for (int i = 0; i < a.finale.size(); i++)
            if (a.finale[i] == true)
                out << i << " ";
        out << "\nTranzitiile sunt:\n";
        for (int i = 0; i < a.nrStari; i++)
            for (int j = 0; j < a.nrStari; j++)
                for (int k = 0; k < 26; k++)
                    if (a.tranzitii[i][j][k] != "")
                        cout << i << " " << j << " " << char(k + 'a') << " " << a.tranzitii[i][j][k] << "\n";
        return out;
    }

    string Transduce(string s) {
        string sol = "";
        int stCur = stare_init;
        for(int poz=0;poz<s.size();poz++)
        {
            int lit = s[poz] - 'a';
            bool gasit = false;
            for (int st2 = 0; st2 < nrStari && (gasit==false); st2++) {
                if (tranzitii[stCur][st2][lit] != "") {
                    sol += tranzitii[stCur][st2][lit];
                    gasit = true;
                    stCur = st2;
                }
            }
            if (gasit == false)
            {
                cout << "cuvantul nu e din limbaj\n";
                return "";
            }
        }
        return sol;
    }

};

int main()
{
    FILE* filePtr;
    freopen_s(&filePtr, "input.txt", "r", stdin);
    Transducer p;
    cin >> p;
    cout << p;
    string s;
    cin >> s;
    cout << s<<"\n";
    cout << p.Transduce(s) << "\n";

   

}
/*
input example:
3
0
1
0
6
0 0 a a
0 1 b a
1 2 a a
1 0 b b
2 1 a b
2 2 b b
baaba

*/
