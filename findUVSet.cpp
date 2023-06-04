#include <bits/stdc++.h>
#include "Graph.h"

using namespace std;

vector<int> findUVSet(int a, int b, const Graph &G, const BFSplus &Ga)
{
    vector<int> Va;
    queue<int> q;
    Va.push_back(b);
    q.push(b);

    vector<bool> A_Nbr(G.v, 0);
    for (auto nbr : G.adj[a])
        A_Nbr[nbr] = 1;

    vector<int> dist(G.v, 0);
    dist[b] = 1;

    while (!q.empty())
    {
        int x = q.front();
        q.pop();

        for (auto c : G.adj[x])
        {
            if (A_Nbr[c])
                continue;

            if (Ga.level[c] > dist[x] + 1)
            {
                dist[c] = dist[x]+1;
                Va.push_back(c);
                q.push(c);
            }
        }
    }

    return Va;
}

void CENDY(Graph &G, vector<float> &Centrality, float &APL, int a, int b)
{
    BFSplus Ga(a,G);
    BFSplus Gb(b,G);
    vector<int> Va = findUVSet(a,b,G,Ga);
    vector<int> Vb = findUVSet(b,a,G,Gb);

    Graph Gp = G;
    Gp.addEdge(a,b);
    vector<float> delta(G.v, 0);

    if(Va.size() < Vb.size())
    {
        for(auto v : Va)
        {
            BFSplus Gv(v,G);
            BFSplus Gvp(v,Gp);
            for(auto u : Vb)
            {
                delta[v]+=abs(Gvp.level[u] - Gv.level[u]);
                delta[u]+=abs(Gvp.level[u] - Gv.level[u]);
            }
        }
    }
    else
    {
        for(auto v : Vb)
        {
            BFSplus Gv(v,G);
            BFSplus Gvp(v,Gp);
            for(auto u : Va)
            {
                delta[v]+=abs(Gvp.level[u] - Gv.level[u]);
                delta[u]+=abs(Gvp.level[u] - Gv.level[u]);
            }
        }
    }

    for(int i=0; i<G.v; i++)
    {
        Centrality[i] = (G.v-1)/((G.v-1)/Centrality[i] - delta[i]);
    }

    vector<bool> inVa(G.v,0);
    vector<bool> inVb(G.v,0);
    for(auto itr : Va)
        inVa[itr]=1;
    for(auto itr : Vb)
        inVb[itr]=1;

    float sum = 0;
    for(int i=0; i<G.v; i++)
    {
        if(inVa[i]||inVb[i])
            sum = sum + delta[i];
    }

    APL = (APL*(G.v*(G.v-1)) - sum)/(G.v*(G.v-1));
    
}


// testing
int main()
{
    Graph g;
    auto v = vector<int>();
    g.addVertex(v);
    v = vector<int>(1, 0);
    g.addVertex(v);

    vector<float> CC = {1, 1};
    float APL = 1;

    v = {1};
    g.addVertex(v);
    v = {0, 2};
    g.addVertex(v);
    v = {1, 3};
    g.addVertex(v);
    v = {2, 3};
    g.addVertex(v);
    v = {2};
    g.addVertex(v);
    v = {5};
    g.addVertex(v);
    v = {6};
    g.addVertex(v);
    BFSplus ga(0, g);
    auto ans = findUVSet(0, 2, g, ga);
    for(auto i : ans)
        cout << i << " ";
    cout << "\n";
    cout << ga.type.size() << "\n";
    return 0;
}