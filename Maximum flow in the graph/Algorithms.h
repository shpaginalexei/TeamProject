#include "Graph.h"

using Algorithm = int(*)(Graph, int, int);

// Method by Shpagin Alexei
int ford_fulkerson_method(Graph graph, int source, int sink);

// Method by Smirnova Anna
int golber_tarjano_algorithm(Graph graph, int source, int sink);