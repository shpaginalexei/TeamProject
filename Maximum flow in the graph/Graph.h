#pragma once
#include <vector>

struct Edge
{
	int from, to;
	int capacity;
	int flow;

	Edge(int from, int to, int capacity)
		: from(from), to(to), capacity(capacity), flow(0) {}

	int get_capacity() const {
		return capacity - flow;
	}
};

struct Graph
{
	Graph(const std::vector<std::vector<int>>&);

	const int V;
	std::vector<std::vector<int>> adj; // IDs of Edges, NOT CAPASITY'S
	std::vector<Edge> edges;	
};