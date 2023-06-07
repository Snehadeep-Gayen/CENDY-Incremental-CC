#ifndef GRAPH_HEADER
#define GRAPH_HEADER

#include <bits/stdc++.h>

using namespace std;

class Graph
{
public:
    int v;                   // no of vertices
    vector<vector<int>> adj; // adjacency list

    Graph();

    void addVertex(vector<int> &neighboursList);
    void addEdge(int u1, int u2);
};

// Implementation
Graph::Graph()
{
    adj = vector<vector<int>>();
    v = 0;
}

void Graph::addVertex(vector<int> &neighbourList)
{
    for (auto i : neighbourList)
        adj[i].push_back(v);
    v++;
    adj.push_back(neighbourList);
}

void Graph::addEdge(int u1, int u2)
{
    adj[u1].push_back(u2);
    adj[u2].push_back(u1);
}

// Class for BFSplus graph
class BFSplus : public Graph
{
public:
    vector<int> level; // level of each vertex

    BFSplus(int vertex, Graph &g);
};

BFSplus::BFSplus(int vertex, Graph &g)
{
    v = g.v;
    adj = g.adj;

    // initialize level of each vertex to -1
    level = vector<int>(v, -1);

    // perform BFS and set level of each vertex
    queue<int> q;
    q.push(vertex);
    level[vertex] = 0;
    while (!q.empty())
    {
        for (int ii = 0; ii < adj[q.front()].size(); ii++)
        {
            int i = adj[q.front()][ii];
            if (level[i] == -1)
            {
                level[i] = level[q.front()] + 1;
                q.push(i);
            }
        }
        q.pop();
    }
}

#endif