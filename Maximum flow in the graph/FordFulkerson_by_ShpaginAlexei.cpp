#include "Graph.h"
#include <iostream>
#include <vector>


using namespace std;


int ford_fulkerson_method(Graph& graph, int source, int sink) {
    int maxFlow = 0;
    vector<int> parent(graph.V, -1);
    //Graph& rgraph = graph;

    while (graph.bfs(source, sink, parent)) {
        cout << "1" << endl;
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