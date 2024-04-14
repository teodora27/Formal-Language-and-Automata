#include <iostream>
#include <vector>
using namespace std;
struct pereche
{
    int nod;
    char litera;
};
class graf
{
private:
    int nr_noduri;
    vector<vector<pereche>> muchii;
    int stare_init;
    vector<int> finale;
public:
    void construiesteDFAdinNFA(graf& NFA)
    {
        nr_noduri = (1 << NFA.nr_noduri);
        muchii.resize(nr_noduri);
        stare_init = 1;
        for (int stare = 1; stare < nr_noduri; stare++)
        {
            bool e_finala = 0;
            vector<int> v(26, 0);
            for (int i = 0; i < NFA.nr_noduri; i++)
                if (stare & (1 << i))
                {
                    for (int j = 0; j < NFA.muchii[i].size(); j++)
                    {
                        char litera = NFA.muchii[i][j].litera;
                        int nod = NFA.muchii[i][j].nod;
                        v[litera - 'a'] |= (1 << nod);
                    }
                    for (int j = 0; j < NFA.finale.size(); j++)
                        if (i == NFA.finale[j])
                            e_finala = 1;
                }
            if (e_finala)
                finale.push_back(stare);
            for (int i = 0; i < 26; i++)
                if (v[i] != 0)
                    muchii[stare].push_back({ v[i], (char)('a' + i) });
        }
    }
    friend istream& operator>>(istream& in, graf& A);
    friend ostream& operator<<(ostream& out, graf& A);
};
istream& operator>>(istream& in, graf& A)
{
    int nr_muchii;
    in >> A.nr_noduri >> nr_muchii;
    A.muchii.resize(A.nr_noduri);
    for (int i = 0; i < nr_muchii; i++)
    {
        int nod1, nod2;
        char litera;
        in >> nod1 >> nod2 >> litera;
        pereche p;
        p.litera = litera;
        p.nod = nod2;
        A.muchii[nod1].push_back(p);
    }
    in >> A.stare_init;
    int nrF;
    in >> nrF;
    //A.finale.resize(nrF);
    for (int i = 0; i < nrF; i++)
    {
        int x;
        in >> x;
        A.finale.push_back(x);
    }
    return in;
}
ostream& operator<<(ostream& out, graf& A)
{
    out << "numarul de stari = ";
    out << A.nr_noduri << "\n";
    out << "tranzitiile sunt:\n";
    for (int i = 0; i < A.muchii.size(); i++)
        for (int j = 0; j < A.muchii[i].size(); j++)
            out << i << " " << A.muchii[i][j].nod << " " << A.muchii[i][j].litera << "\n";
    out << "starea initiala e: " << A.stare_init;
    out << "\nnr de stari finale:" << A.finale.size();
    out << "\nstarile finale sunt: ";
    for (int i = 0; i < A.finale.size(); i++)
        out << A.finale[i] << " ";
    return out;
}
graf NFA, DFA;
int main()
{
    FILE* filePtr;
    freopen_s(&filePtr, "input1.txt", "r", stdin);
    cin >> NFA;
    //cout << NFA;
    DFA.construiesteDFAdinNFA(NFA);
    cout << DFA << "\n";
}
/*
3
6
0 0 a
0 0 b
0 1 a
1 2 b
2 2 a
2 2 b
0
1
2

*/