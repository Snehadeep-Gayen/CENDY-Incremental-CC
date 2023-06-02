vector<int> findUVSet(int a, int b, const Graph &G, const BFSplus &Ga)
{
    vector<int> Va;
    queue<int> q;
    Va.push_back(b);
    q.push(b);

    vector<bool> A_Nbr(G.v,0);
    for(auto nbr : G.adj[a])
        A_Nbr(nbr)=1;
    
    vector<int> dist(G.v,0);
    dist[b]=1;

    while(!q.empty())
    {
        int x = q.front();
        q.pop();
        
        for(auto nbr : G.adj[x])
        {
            if(A_Nbr[nbr])
                continue;
            
            if(Ga.level[nbr] > dist[x]+1)
            {
                Va.push_back(nbr);
                q.push(nbr);
            }
        }
    }

    return Va;
}
