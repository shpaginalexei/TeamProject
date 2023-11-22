#include "Graph.h"
#include <vector>

using namespace std;

int edmonds_karp_algorithm(Graph graph, int source, int sink) {
    int maxFlow = 0;

    while (true) {
        vector<int> parent(graph.V, -1);
        vector<int> minCapacity(graph.V, 0);
        minCapacity[source] = INT_MAX;

        vector<bool> visited(graph.V, false);
        visited[source] = true;

        vector<int> queue;
        int front = 0;
        int rear = 0;
        queue.push_back(source);

        while (front <= rear) {
            int u = queue[front++];
            for (int v = 0; v < graph.V; v++) {
                if (!visited[v] && graph.adj[u][v] > 0) {
                    parent[v] = u;
                    minCapacity[v] = min(minCapacity[u], graph.adj[u][v]);
                    visited[v] = true;
                    queue.push_back(v);
                    rear++;
                }
            }
        }

        if (!visited[sink]) {
            break;
        }

        maxFlow += minCapacity[sink];

        int v = sink;
        while (v != source) {
            int u = parent[v];
            graph.adj[u][v] -= minCapacity[sink];
            graph.adj[v][u] += minCapacity[sink];
            v = u;
        }
    }

    return maxFlow;
}
