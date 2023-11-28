#include "Relabel_to_front.h"
#include "Graph.h"


int relabel_to_front(Graph graph, int source, int drain) {
	RelabelToFront rtb(graph, source, drain);
	return rtb.max_flow();
}