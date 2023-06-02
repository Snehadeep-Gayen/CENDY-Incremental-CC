#ifndef GRAPH_HEADER
#define GRAPH_HEADER

#include <bits/stdc++.h>

using namespace std;

class Graph
{
public:
    int v;  // no of vertices
    vector<vector<int>> adj;

    Graph();

    void addVertex(vector<int> &neighboursList);
    void addEdge(int u1, int u2);
};

Graph::Graph()
{
    adj = vector<vector<int>>();
    v = 0;
}

void Graph::addVertex(vector<int> &neighbourList)
{
    for(auto i : neighbourList)
        adj[i].push_back(v);
    v++;
    adj.push_back(neighbourList);
}

void Graph::addEdge(int u1, int u2)
{
    adj[u1].push_back(u2);
    adj[u2].push_back(u1);
}

#endif