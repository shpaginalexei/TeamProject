#include "Graph.h"
#include "Algorithms.h"
#include <iostream>
#include <chrono>
#include <string>

using namespace std;


void Run(Algorithm alg, Graph& graph, int source, int sink, string description) {
	auto start = chrono::system_clock::now();
	int res = alg(graph, source, sink);
	auto stop = chrono::system_clock::now();
	auto time = chrono::duration_cast<chrono::microseconds>(stop - start).count();

	cout << description << "\nMax flow = " << res  << " (" << time << " msc)" << endl;
}


int main() {

	// example from a presentation from Malinovskaya
	// for this graph MAX FLOW MUST BE 29
	const std::vector<std::vector<int>> adj = { 
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

	Graph graph(adj);

	Run(ford_fulkerson_method, graph, 0, 8, "Ford Fulkerson algorithm (by Shpagin Alexei)");

	return 0;
}
