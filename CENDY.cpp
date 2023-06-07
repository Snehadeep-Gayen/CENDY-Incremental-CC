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

    vector<int> dist = Ga.level;
    dist[b] = 1;

    vector<bool> visited(G.v, 0);
    visited[b] = true;

    while (!q.empty())
    {
        int x = q.front();
        q.pop();

        for (auto c : G.adj[x])
        {
            if (A_Nbr[c])
                continue;
            if(visited[c])
                continue;

            if (Ga.level[c] > dist[x] + 1)
            {
                dist[c] = dist[x]+1;
                Va.push_back(c);
                q.push(c);
                visited[c] = true;
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

    for(int i=1; i<8; i++)
    {
        g.addVertex(v);
        g.addEdge(i, i-1);
    }


    // empty graph on n vertices

    vector<float> CC(8, 0.0);
    float APL = 37.0/14.0;
    CC[0] = 7/28.0;
    CC[1] = 7/22.0;
    CC[2] = 7/18.0;
    CC[3] = 7/16.0;
    CC[4] = CC[3];
    CC[5] = CC[2];
    CC[6] = CC[1];
    CC[7] = CC[0];

    for (int i = 0; i < CC.size(); i++)
    {
        cout << "CC of " << i << " is " << CC[i] << "\n";
    }
    cout << "APL is " << APL << "\n";

    // running cendy
    CENDY(g, CC, APL, 0, 7);

    cout<<"After running CENDY\n";
    
    for(int i=0; i<CC.size(); i++)
    {
        cout<<"CC of "<<i<<" is "<<CC[i]<<"\n";
    }
    cout<<"APL is "<<APL<<"\n";
    g.addEdge(0, 7);
    BFSplus ga(0, g);
    auto ans = findUVSet(0, 2, g, ga);
    for(auto i : ans)
        cout << i << " ";
    cout << "\n";
    return 0;
}