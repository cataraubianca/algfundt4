#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <bits/stdc++.h>
#include <tuple>

using namespace std;

ifstream f("abc.in");
ofstream g("abc.out");

bool vizitat_transpusa[100005], vizitat[100005];

class graf{
private:
    int n, m, cost_total,curent, parinte[100001], dimensiune[100001],distanta[1000];
    vector <vector <int> > muchii;
    priority_queue <pair<int, int>, vector <pair<int,int>>, greater<pair<int,int>>> pq;
    vector <pair<int,int> >graf_ponderat;
    vector<pair<int,pair<int,int>>> muchii_cu_cost;
    vector <bool> InCoada;
    int vizitate[50001];
    vector <int> adj_list[100001];
    vector < pair<int,int> > v[100005];
    //-kosajaru
    vector<int> graf_normal[100005];
    stack<int> S;
    vector<int> graf_transpus[100005];
    vector<int> componente_conexe[100005];


public:
    graf(int n, int m);
    graf(int n);
    void citire_orientat(int m);
    void citire_neorientat(int m);
    void bfs(int s);
    void dfs(int s);
    int conexe(int s);
    bool Havel_Hakimi(vector<int>v, int n);
    void st(int a, vector<int> vizitate, stack<int>& s);
    void sortare_topologica(int n);
    void Citire_cu_transpusa(); //ca sa formeze si transpusa
    void dfs_kosaraju(int nod);
    void dfs_transpus(int nod, int ct);
    void scc();
    //tema 2
    void dijkstra(int nod, vector <pair<int, int>>G[50001]);
    void afiseaza_dijkstra();
    void init_dijkstra(int n);
    void dijkstraa(int n, int m);
    void bellman_ford(int s, vector <pair<int, int>>G[1000]);
    void kruskall();
    int radacina_disjuncte(int n);
    void uniune_disjuncte(int x, int y);
    void init(int n);
    bool aceeasi_padure(int x, int y);
    void disjuncte(int n);
    //tema 3
    void bfs_darb(int s, int &ultim, int &dist_max);
    void darb();
    void roy_floyd(int matrice[105][105]);
    void royfloyd();
    //tema 4
    void CicluEuler();
    void Euler(int Start);
};
//---------------------------------------------------------TEMA-1-------------------------------------------------------//
graf::graf(int n, int m)
{
    this->n=n;
    this->m=m;
}
graf::graf(int n)
{
    this->n=n;
}
void graf::citire_neorientat(int m)
{
    int nod1, nod2;
    for (int i = 0; i <= m; i++)
    {
        f >> nod1 >> nod2;
        muchii[nod1].push_back(nod2);
        muchii[nod2].push_back(nod1);
    }
}
void graf::citire_orientat(int m)
{
    int nod1, nod2;
    for (int i = 0; i <= m; i++)
    {
        f >> nod1 >> nod2;
        muchii[nod1].push_back(nod2);
    }
}

void graf::bfs(int s)
{

    queue<int> q;
    vector<bool> vizitat;
    vector<int> distanta;
    for (int i = 0; i <= n; i++)
    {
        vizitat.push_back(0);
        distanta.push_back(-1);
    }          //populeza vectorii si ii initializeaza ca si nevizitati
    q.push(s); //adaugam in coada s-ul de start si il marcam ca vizitat si distanta 0
    vizitat[s] = true;
    distanta[s] = 0;
    while (!q.empty()) //daca avem elemente in coada, executam:
    {
        int curent = q.front(); //nodul curent devine cel mai vechi nod adaugat in coada
        q.pop();
        //parcurgem lista de adiacenta pt a gasi varfurile adiacente nevizitate ale noduliui curent
        for (auto i:muchii[curent])
        {
            if (!vizitat[i])
            {
                vizitat[i] = true;
                q.push(i);
                distanta[i] = distanta[curent] + 1;
            }
        }
    }

}

void graf::dfs(int s)
{
    vizitate[s] = 1;
    for (int i : muchii[s])
    {
        if (vizitate[i] == 0)
        {
            dfs(i);
        }
    }
}

int graf::conexe(int s)
{   vector<int>vizitate;
    int componente_conexe = 0;
    int i;
    do
    {
        vizitate.push_back(0);
        i++;

    } while (i <= n);

    for (size_t i = 1; i < vizitate.size(); i++)
    {
        if (vizitate[i] == 0)
        {
            dfs(i);
            componente_conexe++;
        }
    }
    return componente_conexe;
}

bool Havel_Hakimi(vector<int> &vect, int n)
{
    bool stare=1;
    while (stare)
    {
        sort(vect.begin(), vect.end(), greater<int>());
        if (vect[0] == 0)
            return true; //verificam daca primul element e 0 dupa sortare

        int a = vect[0];           //salvam valoarea primului el inainte sa il stergem
        vect.erase(vect.begin() + 0); //stergem primul element
        if (a > vect.size())
            return false; //atunci nu vom avea cum sa scadem 1 din primele a elemente ramase
        for (int i = 0; i < a; i++)
        {
            vect[i]--;
            if (vect[i] < 0)
                return false; //oprim executarea deoarece o valoare nu poate fi negativa in cazul in care putem avea graf
        }
    }
}
void graf::st(int a, vector<int> vizitate, stack<int>& s)
{
    vizitate[a]=1; //marcam ca vizitat primul nod
    for(size_t i=1;i< muchii.size()-1;i++)
        if(vizitate[a]==0)//daca gasim un nod nevizitat, aplicam sort top pe el recursiv
            st(i, vizitate, s);
    s.push(a);//punem nodul curent in stack
}
void graf::sortare_topologica(int n)
{
    stack<int> s;
    vector<int> vizitate;
    for(int i=0;i<n;i++)
        vizitate[i]=0; //marcam ca fiind nevizitate

    for(int i=0; i<n;i++)
        if(vizitate[i]==0)
            st(i,vizitate,s);
    while(s.empty()==false)
    {cout<<s.top()<<"";
    s.pop();}//afisam stiva cu rezultatul final

}
void graf :: Citire_cu_transpusa()
{
    for ( int i = 1; i <= m; i++ )
    {   int x, y;
        f >> x >> y;
        graf_normal[x].push_back(y);
        graf_transpus[y].push_back(x);}
}


void graf :: dfs_kosaraju(int nod)
{
    vizitat[nod] = 1;
    for ( auto i : graf_normal[nod] )
        if ( !vizitat[i] )
            dfs_kosaraju(i);
    S.push(nod);
}





void graf :: scc()
{
    int scc_nr = 0;
    while( !S.empty() )
    {   int curent=S.top();
        S.pop();
        if( !vizitat_transpusa[curent] )
        {scc_nr ++;
        dfs_transpus(curent, scc_nr);}
    }

    g<<scc_nr<<endl;
    for (int i=1; i<= scc_nr; i++)
    {
        for(int j: componente_conexe[i] )
                g<<j<<" ";
        g<<endl;
    }
}

void graf :: dfs_transpus(int nod, int ct)
{
    vizitat_transpusa[nod] = 1;
    componente_conexe[ct].push_back(nod);

    for ( auto i : graf_transpus[nod] )
        if ( !vizitat_transpusa[i] )
            dfs_transpus(i, ct);
}

void componente_tare_conexe(){
    int n ,m ;
    f >> n >> m;
    graf G(n, m);
    G.Citire_cu_transpusa();
     for ( int i = 1; i <= n; i++ )
        if ( ! vizitat[i] )
            G.dfs_kosaraju(i);
    G.scc();
}
////------------------------------------------TEMA-2------------------------------------------------------------///
void graf::init_dijkstra(int n){
    for(int i=1;i<=n;i++)
        {distanta[i] = INT_MAX;
        vizitate[i]=false;}
}
void graf::dijkstra(int s, vector <pair<int, int>>G[50001])
{
    init_dijkstra(n);
    distanta[s] = 0;
    pq.push(make_pair(distanta[s], s));
    vizitate[s] = true;

    while(!pq.empty()){
        curent=pq.top().second;
        vizitate[curent]=false;
        pq.pop();

    for(size_t i = 0; i < G[curent].size(); i++)
    {
        int vecin = G[curent][i].first;
        int cost = G[curent][i].second;

        if(distanta[curent] + cost < distanta[vecin])
        {
            distanta[vecin] = distanta[curent] + cost;
            if(!vizitate[vecin])
            {
                pq.push(make_pair(distanta[vecin], vecin));
                vizitate[vecin] = true;
            }


        }
    }

}}
void graf::afiseaza_dijkstra(){
    for(int i = 2; i <= n; i++)
        if(distanta[i] !=INT_MAX)
            g << distanta[i] << " ";
        else
            g <<" 0 "<<" ";
}
void graf::dijkstraa(int n, int m){
    int start_edge, end_edge, cost;
    vector <pair<int, int>>G[50001];
    for(int i = 0; i < m; i++)
    {
        f >> start_edge >> end_edge >> cost;
        G[start_edge].push_back(make_pair(end_edge, cost));
    }
    dijkstra(1, G);
    afiseaza_dijkstra();
}
void graf::bellman_ford (int s, vector <pair<int, int>>G[1000]){
    queue<int>q;
    bool exista_cost_negativ = false;
    for(int i=0;i<n;i++)
        {distanta[i]=INT_MAX;
        InCoada[i]=false;
        vizitate[i]=0;}
    distanta[s]=0;
    q.push(s);
    InCoada[s] = true;
    while(q.empty() == false && exista_cost_negativ == false)
    {
        int nod_curent = q.front();
        vizitate[nod_curent]=1;
        q.pop();
        InCoada[nod_curent]=false;
        for ( size_t i = 0; i < G[nod_curent].size(); i++ )
        {
             int vecin = G[nod_curent][i].first;
             int cost = G[nod_curent][i].second;
             if(distanta[nod_curent]+cost< distanta[vecin])
             {
                 distanta[vecin]=distanta[nod_curent]+cost;
                 if(InCoada[vecin]==false)
                    q.push(vecin);
                    InCoada[vecin]=true;
             }
             vizitate[vecin]++;
             if(vizitate[i]>=n) //adica avem ciclu negativ,avand un nod care isi micsoreaza costul in continuare la mai mult de n-1 iteratii
             {
                 exista_cost_negativ=true;
                 break;
             }
        }
    }
    if (exista_cost_negativ==false){
        for(int i=1; i <=n;i++)
            g<<distanta[i]<<" ";
    }
    else g<<"Graful contine un ciclu negativ";
}
int graf :: radacina_disjuncte(int n)
{
   while(n!=parinte[n]){
        parinte[n]=radacina_disjuncte(parinte[n]);
        return parinte[n];
    }
    return n;
}

void graf :: uniune_disjuncte(int x, int y)
{
    if ( radacina_disjuncte(x) != radacina_disjuncte(y) )
    {
        if ( dimensiune[radacina_disjuncte(x)] > dimensiune[radacina_disjuncte(y)] )
            {parinte[radacina_disjuncte(y)] = radacina_disjuncte(x);
            dimensiune[x] += dimensiune[y];}
        else
        {
            parinte[radacina_disjuncte(x)] = radacina_disjuncte(y);
            dimensiune[y] += dimensiune[x];
        }
    }
}
void graf :: init(int n){
    for ( int i = 1; i <= n; i++ )
        {parinte[i] = i;
        dimensiune[i]=1;}
}

bool graf::aceeasi_padure(int x, int y){
    if (radacina_disjuncte(x)==radacina_disjuncte(y))
        return true;
    return false;
}

void graf :: disjuncte(int n)
{
    int comanda,x,y;

    init(n);
    for (int i = 1;i <= m;i++)
    { f>>comanda>>x>>y;
        if (comanda == 1)
            uniune_disjuncte(x,y);
        else if(comanda ==2)
        {if (aceeasi_padure(x,y))
                g<<"DA\n";
        else g<<"NU\n";}
    }
}

void graf:: kruskall(){

        sort(muchii_cu_cost.begin(),muchii_cu_cost.end());
        for(auto i:muchii_cu_cost) //ne folosim de functiile de la paduri de multimi disjuncte care erau deja implementate
            if(!aceeasi_padure(i.second.first , i.second.second)) //verificam sa nu se formeze ciclu
            {   uniune_disjuncte(i.second.second,i.second.first);
                graf_ponderat.push_back(make_pair(i.second.first, i.second.second)); //adaugam in arborele de afisare
                cost_total=cost_total+i.first;  } //salvam costul
                g<<cost_total<<endl; //afisam costul arborelui

        g<<graf_ponderat.size()<<endl; //afisam nr de linii
        for(size_t i=0; i< graf_ponderat.size(); i++)
            g<<graf_ponderat[i].first<<" "<<graf_ponderat[i].second<<endl; //afisam capetele muchiilor din arbore doua cate doua, cum se specifica in cerinta

}

//---------------------------------------------TEMA-3-------------------------------------------------------------------------------------//
//DARB
 void graf::bfs_darb(int s, int &ultim, int &dist_max) //am modificat primul bfs ca sa poata salva elem si dist pana la el
{
    dist_max=0;
    queue<int> q;
    int vizitat[100001];
    int distanta[100001];
    for (int i = 0; i < n; i++)
        {vizitat[i] = false;
        distanta[i]=0;}        //populeza vectorii si ii initializeaza ca si nevizitati
    q.push(s); //adaugam in coada s-ul de start si il marcam ca vizitat si distanta 0
    vizitat[s] = true;
    distanta[s] = 1;
    while (!q.empty()) //daca avem elemente in coada, executam:
    {
        int curent = q.front(); //nodul curent devine cel mai vechi nod adaugat in coada
        q.pop();
        //parcurgem lista de adicaneta pt a gasi varfurile adiacente nevizitate ale noduliui curent
        for (auto i:adj_list[curent])
        {
            if (!vizitat[i])
            {
                vizitat[i] = true;
                q.push(i);
                distanta[i] = distanta[curent] + 1;
                if(distanta[i]>dist_max)        //atunci cand gasim dist max salvam dist si elem
                {
                    dist_max=distanta[i];
                    ultim=i;
                }
            }
        }
    }

}
void graf::darb(){
    int start_node, end_node, distanta_maxima;
    f >> n;

    int nod1, nod2;
    for(int i = 1; i <= n; ++i)
    {
        f >> nod1 >> nod2;
        adj_list[nod1].push_back(nod2);
        adj_list[nod2].push_back(nod1);
    }

    bfs_darb(1, start_node, distanta_maxima);       //bfs de la nod 1 la prim din bfs final
    bfs_darb(start_node, end_node, distanta_maxima); //bfs de la prim la ultimul nod din bfs final

    g << distanta_maxima;
}
//--------------Roy-Floyd----------------------------------//
void graf::roy_floyd(int matrice[105][105]){
    int i ,j ,k;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if ( matrice[i][j] == 0 && i != j)
                matrice[i][j]==10001;

    for(k=0;k<n;k++)
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                if (matrice[i][k]+matrice[k][j]<matrice[i][j])
                    matrice[i][j]=matrice[i][k]+matrice[k][j];

    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if ( matrice[i][j] == 10001)
                matrice[i][j]==0;

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            g<<matrice[i][j]<<" ";
        g<<endl;
    }
}

void graf::royfloyd(){
    int n,i ,j;
    f>>n;
    int matrice[105][105];
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            f>>matrice[i][j];
    graf G(n);

    G.roy_floyd(matrice);
}
//---------------------------------------------TEMA-4-------------------------------------------------------------------------------------//
//-----------Ciclu-Hamilton-------//
void graf :: Euler(int s)
{
    bool visited[500005];
    for(int i;i<=n;i++)
        visited[i]=false;
    vector <int> rezultat;  //stocam rez final
    vector <int> vect; //dam push_back elem cu care urm sa lucram
    vect.push_back(s);      //adaugam nod start
    while ( !vect.empty() )     //cat timp mai avem elem in vect
    {
        int curent = vect.back(); //noteam el curent
        if ( ! v[curent].empty() ) //daca mai are noduri la care se ajunge pornind din el
        {
            int urm = v[curent].back().first;
            int nr = v[curent].back().second;
            v[curent].pop_back(); //stergem elementul din vector
            if ( ! visited[nr] )    //daca la muchia cu nr respectiv nu s-a ajuns inca
            {
                visited[nr] = true;     //marcam vizitata si o adaugam in vect de prelucrare
                vect.push_back(urm);
            }
        }
        else
        {
            vect.pop_back();        //cand se termina elem stergem elem pe care l-am lucrat
            rezultat.push_back(curent); //il adaugam in vect final
        }
    }
        for ( size_t i = 0; i < rezultat.size(); i++ )
            g << rezultat[i] << " ";
}

void graf :: CicluEuler ()
{
    int x, y, grd[100005];
    bool vizitat[100005];
    for(int i=0; i<=n;i++)
        vizitat[i]=false;
    for ( int i = 1; i <= m; i++ )
    {
        f >> x >> y;
        v[x].push_back( make_pair(y, i) );
        v[y].push_back( make_pair(x, i) );
        grd[x]++;//gradul lui x
        grd[y]++;//gradul lui y
    }

    for ( int i = 0; i <= n; i++ )
        if ( grd[i]%2==1 )
        {
            g << "-1";
            return;
        }

    /*dfs(1); //parcurgere dfs ca sa aflam daca graful e comp conexa

    for(int i=1;i<=n;i++)
    {
        if(vizitat[i]==false)
        {
            g<<-1;
            return;
        }
    }
    */
    Euler(1);
}

int main()
{

}
