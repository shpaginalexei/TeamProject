#include "Graph.h"
#include<queue>
#include<vector>



using namespace std;

bool bfsDinic(const Graph& graph, int source, int sink, vector<int>& level) {
    level.assign(graph.V, -1);
    level[source] = 0;
    queue<int> q;
    q.push(source);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < graph.V; ++v) {
            if (level[v] < 0 && graph.adj[u][v] > 0) {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }

    return level[sink] >= 0;
}

int dfsDinic(Graph& graph, int u, int sink, int flow, vector<int>& level, vector<int>& start) {
    if (u == sink) {
        return flow;
    }

    for (int& v = start[u]; v < graph.V; ++v) {
        if (graph.adj[u][v] > 0 && (level[u] + 1 == level[v])) {
            int currFlow = min(flow, graph.adj[u][v]);
            int minPathFlow = dfsDinic(graph, v, sink, currFlow, level, start);

            if (minPathFlow > 0) {
                graph.adj[u][v] -= minPathFlow;
                graph.adj[v][u] += minPathFlow;
                return minPathFlow;
            }
        }
    }

    return 0;
}

int dinitz_algorithm(Graph graph, int source, int sink) {
    int maxFlow = 0;

    vector<int> level(graph.V, -1);
    vector<int> start(graph.V, 0);

    while (bfsDinic(graph, source, sink, level)) {
        start.assign(graph.V, 0);
        while (int flow = dfsDinic(graph, source, sink, numeric_limits<int>::max(), level, start)) {
            maxFlow += flow;
        }
    }

    return maxFlow;
}
