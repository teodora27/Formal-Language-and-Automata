#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <unordered_set>

using namespace std;
typedef long long ll;

/*
Se considera:
S-simbol de start
A,B,..,Z(mai putin S)-simboluri neterminale
a,b,...,z-simboluri terminale


prodTerminale[1][1] - 0, daca A->a nu exista
                    - 1, altfel

prodNeterminale[1][2][3] - 1, daca exista A->BC
                         - 0, altfel
*/


class grammar {
    int nrProd;
    vector<vector<int>> prodTerminale;
    vector<vector<vector<int>>> prodNeterminale;

public:
    grammar() : prodTerminale(26, vector<int>(26, 0)), prodNeterminale(26, vector<vector<int>>(26, vector<int>(26, 0))), nrProd(0) {}

    friend istream& operator>>(istream& in, grammar& G) {
        in >> G.nrProd;
        in.ignore();//ignora restul liniei
        for (int i = 0; i < G.nrProd; i++) {
            string s;
            getline(in, s);
            assert(s.size() == 3 || s.size() == 4);
            if (s.size() == 3) {
                int st = s[0] - 'A';
                int dr = s[2] - 'a';
                assert(st >= 0 && st < 26 && dr >= 0 && dr < 26);
                G.prodTerminale[st][dr]++;
            }
            else {
                int st = s[0] - 'A';
                int mij = s[2] - 'A';
                int dr = s[3] - 'A';
                assert(st >= 0 && st < 26 && mij >= 0 && mij < 26 && dr >= 0 && dr < 26);
                G.prodNeterminale[st][mij][dr]++;
            }
        }
        return in;
    }

    friend ostream& operator<<(ostream& out, const grammar& G) {
        out << "Productiile terminale sunt:\n";
        for (int i = 0; i < G.prodTerminale.size(); i++) {
            for (int j = 0; j < G.prodTerminale[i].size(); j++) {
                if (G.prodTerminale[i][j] != 0) {
                    out << char(i + 'A') << " -> " << char(j + 'a') << "\n";
                }
            }
        }

        out << "Productiile neterminale sunt:\n";
        for (int i = 0; i < G.prodNeterminale.size(); i++) {
            for (int j = 0; j < G.prodNeterminale[i].size(); j++) {
                for (int k = 0; k < G.prodNeterminale[i][j].size(); k++) {
                    if (G.prodNeterminale[i][j][k] != 0) {
                        out << char(i + 'A') << " -> " << char(j + 'A') << char(k + 'A') << "\n";
                    }
                }
            }
        }
        return out;
    }

    bool apartine(string s) {
        int n = s.size();
        vector<vector<unordered_set<int>>>M(n, vector<unordered_set<int>>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < prodTerminale.size(); j++) {
                if (prodTerminale[j][s[i]-'a'] != 0)
                    M[i][i].insert(j);
            }
        }
        for (int l = 1; l <= n-1; l++) {//pt fiecare sungime
            for (int r = 0; r <= n - l -1; r++) {//pt fiecare inceput
                for (int t = 0; t <= l-1;t++) {//pt fiecare inpartire a cuvantului r/r+l
                    unordered_set<int>L = M[r][r + t];
                    unordered_set<int>R = M[r + t + 1][r + l];
                    for (auto& B : L) {
                        for (auto& C : R) {
                            for (int A = 1; A < prodNeterminale.size(); A++) {
                                if (prodNeterminale[A][B][C] != 0)
                                    M[r][r + l].insert(A);
                            }
                            
                        }
                    }
                }
            }
        }

        if (M[0][n - 1].count('S' - 'A') > 0)
            return true;
        return false;
    }
};

int main() {
    FILE* filePtr;
    freopen_s(&filePtr, "input.txt", "r", stdin);

    grammar G;
    string s;
    cin >> G;
    cout << G;
    cin >> s;
    if (G.apartine(s)==true)
        cout << "Sirul apartine.\n";
    else
        cout << "Sirul nu apartine.\n";
    return 0;
}
