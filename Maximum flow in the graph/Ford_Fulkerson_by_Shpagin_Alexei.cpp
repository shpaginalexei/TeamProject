#include "Graph.h"
#include <vector>
#include <queue>

using namespace std;

bool bfs(Graph graph, int source, int sink, vector<int>& parent) { // parent[] -> path
    vector<bool> visited(graph.V, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < graph.V; v++) {
            if (visited[v] == false && graph.adj[u][v] > 0) {

                if (v == sink) {
                    parent[v] = u;
                    return true;
                }

                parent[v] = u;
                visited[v] = true;
                q.push(v);

            }
        }
    }
    return false;
}

int ford_fulkerson_method(Graph graph, int source, int sink) {
    int maxFlow = 0;
    vector<int> parent(graph.V, -1);

    while (bfs(graph, source, sink, parent)) {
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
