#include "Graph.h"

using namespace std;

Graph::Graph(const vector<vector<int>>& adjacency_matrix) : V(adjacency_matrix.size()) {
	adj.resize(V, vector<int>(V, 0));

	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (adjacency_matrix[i][j] > 0) {
				edges.push_back(Edge(i, j, adjacency_matrix[i][j]));
				adj[i][j] = edges.size();
			}
		}
	}
}
