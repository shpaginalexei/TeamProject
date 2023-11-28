#include "Graph.h"

using Algorithm = int(*)(Graph, int, int);

// Method by Shpagin Alexei
int ford_fulkerson_method(Graph graph, int source, int sink);

// Method by Kotkov Roman
int relabel_to_front(Graph graph, int source, int drain);