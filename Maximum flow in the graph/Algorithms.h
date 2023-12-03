#include "Graph.h"

using Algorithm = int(*)(Graph, int, int);

// Method by Shpagin Alexei
int ford_fulkerson_method(Graph graph, int source, int sink);

// Algorithm by Archakov Ilyas
int edmonds_karp_algorithm(Graph graph, int source, int sink);
// ...