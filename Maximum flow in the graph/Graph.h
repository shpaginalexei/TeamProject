#pragma once
#include <vector>


struct Graph
{
	Graph(const std::vector<std::vector<int>>& adjacency_matrix) : V(adjacency_matrix.size()) {
		adj.resize(V, std::vector<int>(V, 0));

		for (size_t i = 0; i < V; i++) {
			for (size_t j = 0; j < V; j++) {
				adj[i][j] = adjacency_matrix[i][j];
			}
		}
	}

	const int V;
	std::vector<std::vector<int>> adj;
};