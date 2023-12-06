#pragma once
#include "Graph.h"
#include <vector>
#include <string>
#include <fstream>

// examples from a presentation from Malinovskaya

//for this graph MAX FLOW MUST BE 29 (0 -> 8)
const std::vector<std::vector<int>> adj1 = {
	{0, 14,  0, 23,  0,  0,  0,  0,  0},
	{0,  0, 10,  9,  0,  0,  0,  0,  0},
	{0,  0,  0,  0, 12,  0,  0, 18,  0},
	{0,  0,  0,  0, 26,  0,  0,  0,  0},
	{0, 11,  0,  0,  0, 25,  4,  0,  0},
	{0,  0,  0,  0,  0,  0,  7,  8,  0},
	{0,  0,  0,  0,  0,  0,  0,  0, 15},
	{0,  0,  0,  0,  0,  0,  0,  0, 20},
	{0,  0,  0,  0,  0,  0,  0,  0,  0}
};


// for this graph MAX FLOW MUST BE 26 (4 -> 7)
const std::vector<std::vector<int>> adj2 = {
	{0,  3,  0,  0,  2,  0,  0,  0,  0},
	{0,  0,  5, 15, 12,  0,  0,  0,  0},
	{0,  0,  0,  8,  0,  0,  0, 24,  0},
	{6, 15,  8,  0,  0, 18,  4,  0, 11},
	{0, 12,  0,  7,  0, 20,  0,  0,  0},
	{0,  0,  0,  0, 20,  0,  9,  0,  0},
	{0,  0, 10,  4,  0,  9,  0, 16,  0},
	{0,  0, 24,  0,  0,  0, 16,  0, 22},
	{0,  0,  0, 11,  0, 13,  0,  0,  0}
};

std::vector<std::vector<int>> GenerateRandomAdj(const int V, const int max_cap, const int alpha, const std::string file_name);
std::vector<std::vector<int>> GenFullyDenseAcyclicNetwork(const int V_of_one_laler, const int max_cap, const int count_of_layers, const std::string file_name);

struct DataUnit
{
	DataUnit(const std::vector<std::vector<int>>& adj, const int source, const int sink)
		: graph(Graph(adj)), source(source), sink(sink) {}

	DataUnit(const std::string file_name, const int V, const int max_capacity, const int alpha, const int source, const int sink)
		: graph(Graph(GenerateRandomAdj(V, max_capacity, alpha, file_name))), source(source), sink(sink) {}

	DataUnit(const int V_of_one_laler, const int count_of_layers, const int max_capacity, const int source, const int sink, const std::string file_name)
		: graph(Graph(GenFullyDenseAcyclicNetwork(V_of_one_laler, max_capacity, count_of_layers, file_name))), source(source), sink(sink) {}


	const Graph graph;
	const int source;
	const int sink;
};
