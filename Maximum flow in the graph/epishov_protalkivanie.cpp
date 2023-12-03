#include "Graph.h"
#include <vector>

using namespace std;

int pushRelabelMaxFlow(Graph graph, int source, int sink) {
    std::vector<int> height(graph.V, 0);
    std::vector<int> excess(graph.V, 0);
    std::vector<std::vector<int>> flow(graph.V, std::vector<int>(graph.V, 0));

    // Preflow
    height[source] = graph.V;
    for (int i = 0; i < graph.V; ++i) {
        flow[source][i] = graph.adj[source][i];
        flow[i][source] = -graph.adj[source][i];
        excess[i] = graph.adj[source][i];
        excess[source] -= graph.adj[source][i];
    }

    while (true) {
        int u = -1;
        for (int i = 0; i < graph.V; ++i) {
            if (i != source && i != sink && excess[i] > 0 && (u == -1 || height[i] > height[u])) {
                u = i;
            }
        }

        if (u == -1) {
            break;  // No more overflowing vertices
        }

        bool pushed = false;
        for (int v = 0; v < graph.V; ++v) {
            if (graph.adj[u][v] - flow[u][v] > 0 && height[u] == height[v] + 1) {
                int delta = std::min(excess[u], graph.adj[u][v] - flow[u][v]);
                flow[u][v] += delta;
                flow[v][u] -= delta;
                excess[u] -= delta;
                excess[v] += delta;
                pushed = true;
                break;
            }
        }

        if (!pushed) {
            int minHeight = std::numeric_limits<int>::max();
            for (int v = 0; v < graph.V; ++v) {
                if (graph.adj[u][v] - flow[u][v] > 0 && height[v] < minHeight) {
                    minHeight = height[v];
                }
            }

            height[u] = minHeight + 1;
        }
    }

    return excess[sink];
}

