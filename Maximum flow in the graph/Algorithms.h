#include "Graph.h"

using Algorithm = int(*)(Graph, int, int);

// Method by Shpagin Alexei
int ford_fulkerson_method(Graph graph, int source, int sink);

// method pushRelabelMaxFlow
int pushRelabelMaxFlow(Graph graph, int source, int sink);