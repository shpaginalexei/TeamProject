#pragma once
struct Edge {
    int src, dst;
    int capacity, flow;
    size_t rev;
};

struct Boo
{
    Boo(Graph& graph) : V(graph.adj.size()) {
        adj.resize(V, std::vector<Edge>(V, Edge()));

        for (int i = 0; i < graph.V; i++) {
            for (int j = 0; j < graph.V; j++) {
                //add_edge(adj, i, j, graph.adj[i][j]);
                adj[i].push_back({ i, j, graph.adj[i][j], 0, adj[j].size() });
                adj[j].push_back({ j, i, 0, 0, adj[i].size() - 1 });
            }
        }
    }
    const int V;
    std::vector<std::vector<Edge>> adj;
};
