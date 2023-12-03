#include "Graph.h"

using Algorithm = int(*)(Graph, int, int);

// Method by Shpagin Alexei
int ford_fulkerson_method(Graph graph, int source, int sink);

// Algorithm by Archakov Ilyas
int edmonds_karp_algorithm(Graph graph, int source, int sink);

//Method by Dmitrieva Ekaterina
int dinitz_algorithm(Graph graph, int sourse, int sink);

// Method by Kotkov Roman
int relabel_to_front(Graph graph, int source, int drain);

// Method by Smirnova Anna
int golber_tarjano_algorithm(Graph graph, int source, int sink);

// method pushRelabelMaxFlow
int pushRelabelMaxFlow(Graph graph, int source, int sink);

// Algorithm by Caxar
int FlowScalingAlgorithm(Graph graph, int source, int sink);
