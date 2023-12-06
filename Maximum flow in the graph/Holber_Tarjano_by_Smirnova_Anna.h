#pragma once

struct Edge {
    int src, dst;
    int capacity, flow;
    size_t rev;
};

struct HolberTajano
{
    HolberTajano(const Graph& graph, const int source, const int sink) 
        : V(graph.adj.size()), source(source), sink(sink) {
        adj.resize(V, std::vector<Edge>(V, Edge()));

        for (int i = 0; i < graph.V; i++) {
            for (int j = 0; j < graph.V; j++) {
                adj[i].push_back({ i, j, graph.adj[i][j], 0, adj[j].size() });
                adj[j].push_back({ j, i, 0, 0, adj[i].size() - 1 });
            }
        }
    }
    const int V;
    std::vector<std::vector<Edge>> adj;

    // was added for tests
    const int source;
    const int sink;
    int max_flow();
};
