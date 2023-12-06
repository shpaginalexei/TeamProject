#include "Graph.h"
#include <vector>
#include <queue>

using namespace std;

bool dfs(const Graph& graph, int u, int sink, vector<bool>& visited, vector<int>& parent) {
    visited[u] = true;

    for (int v = 0; v < graph.V; v++) {
        if (!visited[v] && graph.adj[u][v] > 0) {
            parent[v] = u;

            if (v == sink) {
                return true;
            }

            if (dfs(graph, v, sink, visited, parent)) {
                return true;
            }
        }
    }

    return false;
}

int ford_fulkerson_method(Graph graph, int source, int sink) {
    int maxFlow = 0;

    while (true) {
        vector<bool> visited(graph.V, false);
        vector<int> parent(graph.V, -1);
        if (!dfs(graph, source, sink, visited, parent)) {
            break;
        }
        int pathFlow = INT_MAX;

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];  
            pathFlow = min(pathFlow, graph.adj[u][v]);
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            graph.adj[u][v] -= pathFlow;
            graph.adj[v][u] += pathFlow;
           
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}
