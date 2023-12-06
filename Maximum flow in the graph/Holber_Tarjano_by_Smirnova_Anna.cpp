#include "Graph.h"
#include "Holber_Tarjano_by_Smirnova_Anna.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <chrono>

int HolberTajano::max_flow() {

    //std::vector<std::vector<Edge>>& adj = adj;
    std::vector<int> excess(V);
    std::vector<int> dist(V), active(V), count(2 * V);
    std::queue<int> Q;

    dist[source] = V;
    active[source] = active[sink] = true;
    count[0] = V - 1;
    count[V] = 1;

    for (auto& e : adj[source]) {
        excess[source] += e.capacity;
        //Push
        int f = std::min(excess[e.src], e.capacity - e.flow);
        if (dist[e.src] <= dist[e.dst] || f == 0) continue;
        e.flow += f;
        adj[e.dst][e.rev].flow -= f;
        excess[e.dst] += f;
        excess[e.src] -= f;
        //Enqueue
        if (!active[e.dst] && excess[e.dst] > 0) {
            active[e.dst] = true;
            Q.push(e.dst);
        }
    }

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        active[u] = false;

        for (auto& e : adj[u]) {
            //Push
            int f = std::min(excess[e.src], e.capacity - e.flow);
            if (dist[e.src] <= dist[e.dst] || f == 0) continue;
            e.flow += f;
            adj[e.dst][e.rev].flow -= f;
            excess[e.dst] += f;
            excess[e.src] -= f;
            //Enqueue
            if (!active[e.dst] && excess[e.dst] > 0) {
                active[e.dst] = true;
                Q.push(e.dst);
            }
        }

        if (excess[u] > 0) {
            if (count[dist[u]] == 1) {
                int k = dist[u]; // Gap Heuristics
                for (int v = 0; v < V; v++) {
                    if (dist[v] < k) continue;
                    count[dist[v]]--;
                    dist[v] = std::max(dist[v], V + 1);
                    count[dist[v]]++;
                    //Enqueue
                    if (!active[v] && excess[v] > 0) {
                        active[v] = true;
                        Q.push(v);
                    }
                }
            }
            else {
                count[dist[u]]--; // Relabel
                dist[u] = 2 * V;
                for (auto& e : adj[u])
                    if (e.capacity > e.flow)
                        dist[u] = std::min(dist[u], dist[e.dst] + 1);
                count[dist[u]]++;
                //Enqueue
                if (!active[u] && excess[u] > 0) {
                    active[u] = true;
                    Q.push(u);
                }
            }
        }
    }
    int flow = 0;
    for (const auto& e : adj[source]) flow += e.flow;
    return flow;
}

int golber_tarjano_algorithm(Graph graph1, int source, int sink) {

    HolberTajano graph(graph1, source, sink);
    std::vector<std::vector<Edge>>& adj = graph.adj;
    std::vector<int> excess(graph.V);
    std::vector<int> dist(graph.V), active(graph.V), count(2 * graph.V);
    std::queue<int> Q;

    dist[source] = graph.V;
    active[source] = active[sink] = true;
    count[0] = graph.V - 1;
    count[graph.V] = 1;

    for (auto& e : adj[source]) {
        excess[source] += e.capacity;
        //Push
        int f = std::min(excess[e.src], e.capacity - e.flow);
        if (dist[e.src] <= dist[e.dst] || f == 0) continue;
        e.flow += f;
        adj[e.dst][e.rev].flow -= f;
        excess[e.dst] += f;
        excess[e.src] -= f;
        //Enqueue
        if (!active[e.dst] && excess[e.dst] > 0) {
            active[e.dst] = true;
            Q.push(e.dst);
        }
    }

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        active[u] = false;

        for (auto& e : adj[u]) {
            //Push
            int f = std::min(excess[e.src], e.capacity - e.flow);
            if (dist[e.src] <= dist[e.dst] || f == 0) continue;
            e.flow += f;
            adj[e.dst][e.rev].flow -= f;
            excess[e.dst] += f;
            excess[e.src] -= f;
            //Enqueue
            if (!active[e.dst] && excess[e.dst] > 0) {
                active[e.dst] = true;
                Q.push(e.dst);
            }
        }

        if (excess[u] > 0) {
            if (count[dist[u]] == 1) {
                int k = dist[u]; // Gap Heuristics
                for (int v = 0; v < graph.V; v++) {
                    if (dist[v] < k) continue;
                    count[dist[v]]--;
                    dist[v] = std::max(dist[v], graph.V + 1);
                    count[dist[v]]++;
                    //Enqueue
                    if (!active[v] && excess[v] > 0) {
                        active[v] = true;
                        Q.push(v);
                    }
                }
            }
            else {
                count[dist[u]]--; // Relabel
                dist[u] = 2 * graph.V;
                for (auto& e : adj[u])
                    if (e.capacity > e.flow)
                        dist[u] = std::min(dist[u], dist[e.dst] + 1);
                count[dist[u]]++;
                //Enqueue
                if (!active[u] && excess[u] > 0) {
                    active[u] = true;
                    Q.push(u);
                }
            }
        }
    }
    int flow = 0;
    for (const auto& e : adj[source]) flow += e.flow;
    return flow;
}