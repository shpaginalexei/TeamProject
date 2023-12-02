#include "Graph.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

struct Edge {
    int from, to, capacity, flow;

    Edge(int from, int to, int capacity) : from(from), to(to), capacity(capacity), flow(0) {}
};

int findAugmentingPath(Graph& graph, int source, int sink, int delta) {
    vector<int> parent(graph.V, -1);
    vector<int> minCapacity(graph.V, INT_MAX);
    vector<bool> visited(graph.V, false);

    queue<int> q;
    q.push(source);
    visited[source] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int i = 0; i < graph.V; ++i) {
            if (!visited[i] && graph.adj[current][i] >= delta) {
                q.push(i);
                visited[i] = true;
                parent[i] = current;
                minCapacity[i] = min(minCapacity[current], graph.adj[current][i]);
            }
        }
    }

    if (!visited[sink]) {
        return 0; // No augmenting path found
    }

    int pathFlow = minCapacity[sink];
    int current = sink;
    while (current != source) {
        int prev = parent[current];
        graph.adj[prev][current] -= pathFlow;
        graph.adj[current][prev] += pathFlow;
        current = prev;
    }

    return pathFlow;
}

int FlowScalingAlgorithm(Graph graph, int source, int sink) {
    int maxCapacity = INT_MIN;
    for (int i = 0; i < graph.V; ++i) {
        for (int j = 0; j < graph.V; ++j) {
            maxCapacity = max(maxCapacity, graph.adj[i][j]);
        }
    }

    int delta = 1;
    while (delta < maxCapacity) {
        delta *= 2;
    }

    int maxFlow = 0;
    for (; delta >= 1; delta /= 2) {
        while (int pathFlow = findAugmentingPath(graph, source, sink, delta)) {
            maxFlow += pathFlow;
        }
    }

    return maxFlow;
}

