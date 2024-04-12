#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

struct pereche {
    int nod;
    char litera;
};
bool e_in_vector(int x, vector<int> v)
{
    for (int i = 0; i < v.size(); i++)
        if (v[i] == x)
            return true;
    return false;
}
bool sortare(pereche a, pereche b)
{
    return a.litera - 'a' < b.litera - 'a';
}

class graf {

    int nr_noduri;
    vector<int> noduri;
    int nr_muchii;
    vector<vector<pereche>>muchii;
    int stare_init;
    int nrF;
    vector<int>finale;


    vector<int> vizitat;
    vector<int> vizitat2;
    map<int, vector<int>>partitii;
public:
    map<int, vector<int>>get_partitii() { return partitii; }
    void set_partitii(map<int, vector<int>>p) { partitii=p; } 
    graf remake_DFA()
    {
        graf DFA_fin;
        DFA_fin.nr_noduri = partitii.size();
        DFA_fin.noduri.resize(partitii.size());
        for (int i = 0; i < partitii.size(); i++)
            DFA_fin.noduri[i] = i;
        DFA_fin.stare_init = stare_init;
        DFA_fin.finale.clear();
        DFA_fin.nrF = 0;
        for (int i = 0; i < partitii.size(); i++)
        {
            if (e_finala(partitii[i][0]))
            {
                DFA_fin.nrF++;
                DFA_fin.finale.push_back(i);
            }
        }
        DFA_fin.nr_muchii = 0;
        DFA_fin.muchii.clear();
        DFA_fin.muchii.resize(partitii.size());
        
        for (int i = 0; i < partitii.size(); i++)
        {
            //merg prin muchiile elementului partitii[i][0]
            //pemtru muchia (litera nod) adaug muchia (litera ce_partitie(nod))
            for (int j = 0; j < muchii[partitii[i][0]].size(); j++)
            {
                //cout << "sunt aici " << muchii[partitii[i][0]][j].litera << " " << muchii[partitii[i][0]][j].nod;
                pereche p;
                p.litera = muchii[partitii[i][0]][j].litera;
                p.nod =ce_partitie( muchii[partitii[i][0]][j].nod,partitii);
                DFA_fin.muchii[i].push_back(p);
                DFA_fin.nr_muchii++;
            }
        }
        return DFA_fin;
    }
    int ce_partitie(int x, map<int, vector<int>>partitii)
    {
        for (int i = 0; i < partitii.size(); i++)
            for (int j = 0; j < partitii[i].size(); j++)
                if (partitii[i][j] == x)
                    return i;
    }
    void partitionare1()
    {
        for (int i = 0; i < noduri.size(); i++)
        {
            if (!e_finala(noduri[i]))
                partitii[0].push_back(noduri[i]);
            else
                partitii[1].push_back(noduri[i]);
        }
        /*cout << "\n-----------------------------------------------------------------------------------\n";
        cout << "\nprima partitionare:\n";
        for (int i = 0; i < 2; i++)
        {
            cout << "partitie "<<i<<": ";
            for (int j = 0; j < partitii[i].size(); j++)
                cout << partitii[i][j] << " ";
            cout << "\n";
        }*/
    }
    bool echivalente(int stare1, int  stare2)
    {
        int ok = 1;
        sort(muchii[stare1].begin(), muchii[stare1].end(), sortare);
        /*cout << "muchii " << stare1 << ": ";
        for(int i=0;i<muchii[stare1].size();i++)
            cout<<"("<<muchii[stare1][i].litera*/
        sort(muchii[stare2].begin(), muchii[stare2].end(), sortare);
        if (muchii[stare1].size() != muchii[stare2].size())
            return false;
        for (int i = 0; i < muchii[stare1].size(); i++)
        {
            if (muchii[stare1][i].litera - 'a' != muchii[stare2][i].litera - 'a')
                return false;
            if (muchii[stare1][i].nod != muchii[stare2][i].nod )
                return false;
        }
        return true;

    }
    map<int, vector<int>> repartitionare(map<int, vector<int>>partitii)
    {
        int nr_partitii = partitii.size();
        int nr_partitii2 = nr_partitii;
        for (int i = 0; i < nr_partitii; i++)
        {
            int ok = 0;
            //partitia i
            for (int j = 1; j < partitii[i].size(); j++)
            {
                if (!echivalente(partitii[i][0], partitii[i][j]))
                {
                    partitii[nr_partitii2].push_back(partitii[i][j]);
                    swap(partitii[i][j], partitii[i][partitii[i].size() - 1]);
                    partitii[i].pop_back();
                    ok = 1;
                }
            }
            if (ok == 1)
                nr_partitii2++;
        }
       /* cout << "\n-----------------------------------------------------------------------------------\n";
        cout << "\npartitionare:\n";
        for (int i = 0; i < partitii.size(); i++)
        {
            cout << "partitie " << i << ": ";
            for (int j = 0; j < partitii[i].size(); j++)
                cout << partitii[i][j] << " ";
            cout << "\n";
        }*/
        return partitii;
    }
    bool partitii_la_fel(map<int, vector<int>>p1, map<int, vector<int>>p2)
    {
        if (p1.size() != p2.size())
            return false;
        return true;
    }

    bool e_finala(int stare)
    {
        for (int i = 0; i < finale.size(); i++)
            if (finale[i] == stare)
                return true;
        return false;
    }
    bool DFS(int stare, int cnt)
    {
        if (cnt == nr_noduri + 5)
            return false;
        if (e_finala(stare))
        {
            return true;
        }
        
        
        vizitat2.resize(nr_noduri);
        vizitat2[stare] = 1;
        for (int i = 0; i < muchii[stare].size(); i++)
        {
            if (vizitat2[muchii[stare][i].nod] == 0)
                if (DFS(muchii[stare][i].nod, cnt + 1))
                    return true;
        }
        return false;
        //vizitat2[stare] = 0;
    }
    void parcurgere(int stare)
    {
        vizitat.resize(nr_noduri);
        vizitat[stare] = 1;
        for (int i = 0; i < muchii[stare].size(); i++)
        {
            if (vizitat[muchii[stare][i].nod] == 0)
                parcurgere(muchii[stare][i].nod);
        }
    }
    graf scoatere_noduri()
    {
        //vectorul "scoate" contine unreachable states si starile din care nu se poate ajunge in finala
        parcurgere(stare_init);
        vector<int> scoate;
        cout << "stari de scos: ";
        for (int i = 0; i < nr_noduri; i++)
            if (vizitat[i] == 0)
                scoate.push_back(i);

        for (int i = 0; i < nr_noduri; i++)
        {
            if (DFS(noduri[i], 0) == false&& !e_in_vector(i, scoate))
                scoate.push_back(i);
        }
        for (int i = 0; i < scoate.size(); i++)
            cout << scoate[i] << " ";
        cout << "\n";

        //creez DFA_mini cu toate starile mai putin cele din scoate
        graf DFA_mini;
        DFA_mini.nr_noduri = nr_noduri-scoate.size();
        for (int i = 0; i < nr_noduri; i++)
        {
            if (!e_in_vector(noduri[i], scoate))
                DFA_mini.noduri.push_back(noduri[i]);
        }
        
        DFA_mini.muchii.resize(nr_muchii);    
        for (int i = 0; i < nr_noduri; i++)
        {
            for(int j=0;j<muchii[i].size();j++)
                if (!e_in_vector(muchii[i][j].nod, scoate) && !e_in_vector(noduri[i], scoate))
                {
                    pereche p;
                    p.litera = muchii[i][j].litera;
                    p.nod = muchii[i][j].nod;
                    DFA_mini.muchii[i].push_back(p);
                }
        }
        DFA_mini.stare_init = stare_init;
        for (int i = 0; i < nrF; i++)
            if(!e_in_vector(finale[i],scoate))
            DFA_mini.finale.push_back(finale[i]);
        DFA_mini.nrF = DFA_mini.finale.size();
        //cout << DFA_mini;

        return DFA_mini;
    }

    friend istream& operator>>(istream& in, graf& A);
    friend ostream& operator<<(ostream& out, graf& A);
};
istream& operator>>(istream& in, graf& A)
{
    in >> A.nr_noduri;
    for (int i = 0; i < A.nr_noduri; i++)
    {
        int nod;
        in >> nod;
        A.noduri.push_back(nod);
    }
    in >> A.nr_muchii;
    A.muchii.resize(A.nr_noduri);
    for (int i = 0; i < A.nr_muchii; i++)
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
    in >> A.nrF;
    for (int i = 0; i < A.nrF; i++)
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
    cout << "starile sunt: ";
    for (int i = 0; i < A.noduri.size(); i++)
        cout << A.noduri[i] << " ";
    out << "\nnumarul de tranzitii = ";
    out << A.nr_muchii;
    out << "\ntranzitiile sunt:\n";
    for (int i = 0; i < A.muchii.size(); i++)
    {
        for (int j = 0; j < A.muchii[i].size(); j++)
            out << i << " " << A.muchii[i][j].nod << " " << A.muchii[i][j].litera << "\n";
    }
    out << "starea initiala e: " << A.stare_init;
    out << "\nnr de stari finale: " << A.nrF;
    out << "\nstarile finale sunt: ";
    for (int i = 0; i < A.finale.size(); i++)
    {
        out << A.finale[i] << " ";
    }
    return out;
}


 graf DFA, DFA_min;



int main()
{
    FILE* filePtr;
    freopen_s(&filePtr, "input.txt", "r", stdin);
    cin >> DFA;
    //cout << DFA;
    //cout << "\n-----------------------------------------------------------------------------------\n";
    DFA_min = DFA.scoatere_noduri(); 
       cout << DFA_min;

    //partitionare
    DFA_min.partitionare1();   
    map<int, vector<int>> partitii_curent = DFA_min.get_partitii();
    map<int, vector<int>> partitii_nou;

    while (true) {
        partitii_nou = DFA_min.repartitionare(partitii_curent);
        if (DFA_min.partitii_la_fel(partitii_curent, partitii_nou))
            break; 
        partitii_curent = partitii_nou;
    }
    cout << "\n-----------------------------------------------------------------------------------\n";

    DFA_min.set_partitii(partitii_curent);
    DFA_min=DFA_min.remake_DFA();
    cout << DFA_min;
}

    
