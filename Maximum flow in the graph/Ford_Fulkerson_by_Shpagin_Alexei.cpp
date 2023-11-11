#include "Graph.h"
#include <vector>
#include <queue>

using namespace std;

bool bfs(Graph& graph, int source, int sink, vector<int>& parent) { // parent[] -> path
    vector<bool> visited(graph.V, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < graph.V; v++) {
            int edgeIndex = graph.adj[u][v] - 1;
            if (edgeIndex >= 0) {
                Edge& edge = graph.edges.at(edgeIndex);
                if (!visited[v] && (edge.get_capacity() > 0)) {
                    parent[v] = edgeIndex;
                    visited[v] = true;
                    q.push(v);

                    if (v == sink) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int ford_fulkerson_method(Graph graph, int source, int sink)
{
    int maxFlow = 0;
    vector<int> parent(graph.V, -1);

    while (bfs(graph, source, sink, parent)) {
        int pathFlow = INT_MAX;

        for (int v = sink; v != source; v = graph.edges[parent[v]].from) {
            int edgeIndex = parent[v];
            Edge& edge = graph.edges[edgeIndex];
            pathFlow = min(pathFlow, edge.capacity - edge.flow);
        }

        for (int v = sink; v != source; v = graph.edges[parent[v]].from) {
            int edgeIndex = parent[v];
            int reverseEdgeIndex = graph.adj[graph.edges[edgeIndex].to][graph.edges[edgeIndex].from];
            graph.edges[edgeIndex].flow += pathFlow;
            graph.edges[reverseEdgeIndex].flow -= pathFlow;
           
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}
