#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

class graf
{
private:
    int nr_noduri;
    vector<vector<int>> muchii;
    /*
      a  b  c
    0
    1 
    2
    3
    4
    5

    */
    int stare_init;
    vector<bool> finale;

    vector<int>partitie;
    vector<bool>unreachable;
    vector<bool>vizitat;
public:
    void alta_stare_init() {
        //creeaza o noua stare initiala, care sa nu fie pe un ciclu
        nr_noduri++;
        muchii.push_back(vector<int>(26, -1));
        muchii[nr_noduri - 1] = muchii[stare_init];
        finale.push_back(false);
       
        if (finale[stare_init] == true)
            finale[nr_noduri - 1] = true;
        stare_init = nr_noduri - 1;
    }
    void completeazaDFA() {
        //adauga un sink state
        nr_noduri++;
        muchii.push_back(vector<int>(26, nr_noduri-1));
        finale.push_back(false);
        for (int i = 0; i < muchii.size(); i++)
            for (int j = 0; j < 26; j++)
                if (muchii[i][j] == -1)
                    muchii[i][j] = nr_noduri - 1;
        /*for (int i = 0; i < muchii.size(); i++)
        {
            for (int j = 0; j < 26; j++)
                cout << muchii[i][j] << " ";
            cout << "\n";
        }*/


    }
    void scoate_unreachable(){
        unreachable.resize(nr_noduri,false);
        vizitat.resize(nr_noduri, false);
        DFS(stare_init);
        for (int i = 0; i < nr_noduri; i++)
            if (vizitat[i] == false)
                unreachable[i] = true;
        /*cout << "\n";
        for (int i = 0; i < nr_noduri; i++)
            cout<<unreachable[i]<<" ";
        cout << "\n";*/
    }
    void DFS(int stare) {
        if (vizitat[stare] == true)
            return;
        vizitat[stare] = true;
        for (int j = 0; j < 26; j++)
            if (vizitat[muchii[stare][j]] == false)
                DFS(muchii[stare][j]);
    }
    void prima_partitionare() {
        partitie.resize(nr_noduri, -1);
        for (int i = 0; i < nr_noduri; i++)
            if(!unreachable[i])
            {
                if (!finale[i])
                    partitie[i] = 0;
                else
                    partitie[i] = 1;
            }
        /*for (int i = 0; i < nr_noduri; i++)
            cout << partitie[i] << " ";
        cout << "\n";*/
    }
    void repartitionare() {
        while(true)
        {
            /*for (int i = 0; i < partitie.size(); i++)
                cout << partitie[i] << " ";
            cout << "\n";*/
            vector<int>partitie2 = partitie;
            for (int part = 0; part < nr_noduri; part++)
            {
                vector<pair<vector<int>, int>>reprezentare(0);
                //pentru fiecare element stocam 
                //un vector cu partitiile in care duce fiecare litera
                //vaoarea nodului
                //cout << "partitia " << part << "\n";
                for (int i = 0; i < nr_noduri; i++)
                    if (partitie[i] == part)
                    {
                        //cout << i << " :";
                        vector<int>repi(26);
                        for (int j = 0; j < 26; j++)
                        {
                            repi[j] = partitie[muchii[i][j]];
                            //cout << repi[j] << " ";
                        }
                        reprezentare.push_back({ repi,i });
                        //cout << "\n";
                    }
                if (reprezentare.size() == 0)
                    break;
                sort(reprezentare.begin(), reprezentare.end());
                 /*for (int i = 0; i < reprezentare.size(); i++)
                     cout << reprezentare[i].second << " ";
                 cout << "\n";*/
                 //prima grupa de elem raman in partitia in care sunt
                int primul = 0, ultimul = 0;
                while (ultimul < reprezentare.size() && reprezentare[ultimul].first == reprezentare[primul].first)
                    ultimul++;
                //cout << "verificare" << (reprezentare[0].first == reprezentare[1].first) << "\n";
                primul = ultimul;

                int ptt = ((int)*max_element(partitie2.begin(), partitie2.end())) + 1;
                while (ultimul < reprezentare.size() )
                {
                    while (ultimul <= reprezentare.size() - 1 && reprezentare[ultimul].first == reprezentare[primul].first)
                    {
                        partitie2[reprezentare[ultimul].second] = ptt;
                        ultimul++;
                    }
                    primul = ultimul;
                    ptt++;
                }
            }
            if (normalizare(partitie) == normalizare(partitie2))
                break;

            partitie = partitie2;
             /*cout << "repartitionat:";
             for (int i = 0; i < nr_noduri; i++)
                 cout << partitie[i] << " ";
             cout << "\n";*/
            partitie = normalizare(partitie);
            /* cout << "repartitionat:";
             for (int i = 0; i < nr_noduri; i++)
                 cout << partitie[i] << " ";
             cout << "\n";*/
        }
    }
    vector<int> normalizare(vector<int>p)
    {
        map<int, int>mp;
        mp[-1] = -1;
        int nr = 0;
        for (int i = 0; i < p.size(); i++)
            if (mp.count(p[i]) == 0)
                mp[p[i]] = nr++;
        for (int i = 0; i < p.size(); i++)
            p[i] = mp[p[i]];
        return p;
    }
    void show_partitie() {
        for (int i = 0; i < partitie.size(); i++)
            cout << partitie[i] << " ";
    }
    void DFA_mini() {
        
        vector<vector<int>>muchii_mini(*max_element(partitie.begin(), partitie.end())+1, vector<int>(26,-1));
        //e o matrice de n*26, unde n este numarul de partitii
        for (int i = 0; i <nr_noduri; i++)
        {
            if (partitie[i] == -1)
                continue;
            for (int j = 0; j < 26; j++)
                if (muchii_mini[partitie[i]][j] == -1)
                    muchii_mini[partitie[i]][j] = partitie[muchii[i][j]];
        }

        /*cout << "\n";
        for(int i=0;i< muchii_mini.size();i++)
        {
            for (int j = 0; j < 26; j++)
                cout << muchii_mini[i][j] << " ";
            cout << "\n";
        }*/

        //fac 2 vectori graf2, graf2inv
        //graf2 contine pt fiecare nod perechi de forma {nod, litera} pentru nodurile in care poate ajunge
        //graf2inv contine pt fiecare nod perechi de forma {nod, litera} pentru nodurile care ajung in el
        vector<vector<pair<int,int>>>graf2(muchii_mini.size()), graf2inv(muchii_mini.size());
        for (int i = 0; i < muchii_mini.size(); i++)
        {
            for(int j=0;j<26;j++)
            {
                graf2[i].push_back({muchii_mini[i][j],j});
                graf2inv[muchii_mini[i][j]].push_back({ i,j });
            }
        }
        //cout << "ok";
        //cout << "\n";
        //for (int i = 0;i < graf2.size(); i++)
        //{
        //    cout << "nodul " << i << ": ";
        //    for (int j = 0; j < 2/*graf2[i].size()*/; j++)
        //    {
        //        cout << "(" << graf2[i][j].first << "," << (char)(graf2[i][j].second + 'a') << ")";
        //    }
        //    cout << "\n";
        //}
        //trebuie sa elim unreachable si starile care nu ajung in starea finala
        //pentru toate starile care nu sunt bune setez unreachable[i]=true
        vizitat.clear();
        vizitat.resize(graf2.size(),false);
        /*cout << "\nstare init:" << partitie[stare_init]<<"\n";
        cout << "trece prin:";*/
        dfs2(partitie[stare_init],graf2);

        unreachable.clear();
        unreachable.resize(graf2.size(), false);
        for (int i = 0; i < graf2.size(); i++)
            if (vizitat[i] == false)
                unreachable[i] = true;
        
        //exit(0);
        //starile care nu ajung in finala
        vector<int>finaleinitial;
        vizitat.clear();
        vizitat.resize(graf2inv.size(),false);
        for (int i = 0; i < finale.size(); i++)
            if (finale[i] == true&&partitie[i]!=-1)
            {
                dfs2(partitie[i], graf2inv);
                finaleinitial.push_back(i);
            }

        for (int i = 0; i < graf2.size(); i++)
            if (vizitat[i] == false)
                unreachable[i] = true;
        
        int valide = 0;
        vector<int>rearanjare(graf2.size(),-1);
        for (int i = 0; i < graf2.size(); i++)
        {
            if (!unreachable[i])
            {
                rearanjare[i] = valide;
                valide++;
            }
        }
        /*for (int i = 0; i < rearanjare.size(); i++)
            cout << rearanjare[i] << " ";
        cout << "\n";*/
        cout<< "numarul de stari = "<<valide<<"\n";
        cout << "starea initiala e = " << rearanjare[partitie[stare_init]]<<"\n";
        cout << "starile finale sunt = ";
        set<int>am_pus;
        for (int i = 0; i < finaleinitial.size(); i++)
        {
            if (!unreachable[partitie[finaleinitial[i]]])
            {
                if (am_pus.count(partitie[finaleinitial[i]]) != 0)
                    continue;
                am_pus.insert(partitie[finaleinitial[i]]);
                cout << partitie[finaleinitial[i]] << " ";
            }
        }
        cout << "\ntranzitiile sunt:\n";
        for (int i = 0; i < graf2.size(); i++)
        {
            if (unreachable[i])
                continue;
            for (int j = 0; j < graf2[i].size(); j++)
                if(!unreachable[graf2[i][j].first])
                cout << i << " " << graf2[i][j].first << " " << (char)(graf2[i][j].second + 'a') << "\n";
        }

    }
    void dfs2(int stare, vector<vector<pair<int, int>>>&graf2) {
        //cout << "stare = " << stare << " " << (int)vizitat.size() << " " << vizitat[stare] << "\n";
        if (vizitat[stare])
            return;
        vizitat[stare] = true;
        //cout << "sunt la starea " << stare<< " "<<vizitat[0] << "\n";
        for (int i = 0; i < graf2[stare].size(); i++)
        {
            //cout << vizitat[graf2[stare][i].first] << " ";
            if (!vizitat[graf2[stare][i].first])
                dfs2(graf2[stare][i].first, graf2);
        }
    }

   
    friend istream& operator>>(istream& in, graf& A);
    friend ostream& operator<<(ostream& out, graf& A);
};
istream& operator>>(istream& in, graf& A)
{
    int nr_muchii;
    in >> A.nr_noduri >> nr_muchii;
    A.muchii.resize(A.nr_noduri,vector<int>(26,-1));
    for (int i = 0; i < nr_muchii; i++)
    {
        int nod1, nod2;
        char litera;
        in >> nod1 >> nod2 >> litera;
        nod1--;
        nod2--;
        A.muchii[nod1][litera - 'a'] = nod2;
    }
    //cout << "\ncitest init";
    in >> A.stare_init;
    //cout << "starea initiala" << A.stare_init;
    A.stare_init--;
    int nrF;
    in >> nrF;
    A.finale.resize(A.nr_noduri);
    for (int i = 0; i < nrF; i++)
    {
        int x;
        in >> x;
        x--;
        A.finale[x] = true;
    }
    return in;
}
ostream& operator<<(ostream& out, graf& A)
{
    out << "numarul de stari = ";
    out << A.nr_noduri << "\n";
    out << "tranzitiile sunt:\n";
    for (int i = 0; i < A.muchii.size(); i++)
        for (int j = 0; j < 26; j++)
            if(A.muchii[i][j]!=-1)
            out << i << " " << A.muchii[i][j] << " " << (char)(j + 'a') << "\n";
    out << "starea initiala e: " << A.stare_init;
    out << "\nstarile finale sunt: ";
    for (int i = 0; i < A.finale.size(); i++)
        if(A.finale[i]==true)
        out << i << " ";
    return out;
}
graf DFA;
int main()
{
    FILE* filePtr;
    freopen_s(&filePtr, "input1.txt", "r", stdin);
    cin >> DFA;
    //cout << DFA;
    DFA.alta_stare_init();
    DFA.completeazaDFA();
    DFA.scoate_unreachable();
    DFA.prima_partitionare();


    DFA.repartitionare();
    //DFA.show_partitie();
    DFA.DFA_mini();
    //cout << DFA;
    
}
