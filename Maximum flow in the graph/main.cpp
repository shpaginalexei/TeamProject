#include "Graph.h"
#include "Algorithms.h"
#include "Data.h"
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

	cout << "\t Graph 1\n";
	Graph graph1(adj1);
	Run(ford_fulkerson_method, graph1, 0, 8, "Ford Fulkerson algorithm (by Shpagin Alexei)");
	Run(dinitz_algorithm, graph1, 0, 8, "Dinitz algoritm (by Dmitrieva Ekaterina)");
	Run(edmonds_karp_algorithm, graph1, 0, 8, "Edmonds Karp algorithm (by Archakov Ilyas)");
	// ...
	
	cout << "\n\t Graph 2\n";
	Graph graph2(adj2);
	Run(ford_fulkerson_method, graph2, 4, 7, "Ford Fulkerson algorithm (by Shpagin Alexei)");
	Run(dinitz_algorithm, graph2, 4, 7, "Dinitz algoritm (by Dmitrieva Ekaterina)");
	Run(edmonds_karp_algorithm, graph2, 4, 7, "Edmonds Karp algorithm (by Archakov Ilyas)");
	// ...

	return 0;
}
