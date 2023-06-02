void CENDY(const Graph &G, vector<float> &Centrality, float &APL, int a, int b)
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
