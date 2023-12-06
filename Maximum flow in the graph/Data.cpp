#include "Data.h"
#include <fstream>
#include <string>
#include <random>
#include <iostream>

using namespace std;

vector<vector<int>> GenerateRandomAdj(const int V, const int max_cap, const int alpha, const string file_name) {
    vector<vector<int>> adj(V, vector<int>(V, 0));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(-max_cap * alpha, max_cap);

    int E = 0;
    ofstream file;
    file.open(".adj/" + file_name, ios::out);
    if (file.is_open()) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                int cap = dist(gen);
                adj[i][j] = cap > 0 ? cap : 0;
                file << adj[i][j] << ", ";
                E = adj[i][j] > 0 ? E + 1 : E;
            }
            file << "\n";
        }
    }
    file.close();

    cout << "File '" << file_name << "' was generated (V = " << V << ", E = " << E << ")\n";
    return adj;
}

vector<vector<int>> GenFullyDenseAcyclicNetwork(const int V_of_one_laler, const int max_cap, const int count_of_layers, const string file_name) {
    int V = V_of_one_laler * count_of_layers + 2;
    vector<vector<int>> adj(V, vector<int>(V, 0));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, max_cap);

    ofstream file;
    file.open(".adj/" + file_name, ios::out);
    if (file.is_open()) {

        for (int j = 0; j < V_of_one_laler; j++) {
            adj[0][j + 1] = dist(gen);
        }

        for (int l = 0; l < count_of_layers - 1; l++) {
            for (int i = 0; i < V_of_one_laler; i++) {
                for (int j = 0; j < V_of_one_laler; j++) {
                    adj[l * V_of_one_laler + i + 1][(l + 1) * V_of_one_laler + j + 1] = dist(gen);
                }
            }
        }

        for (int j = 0; j < V_of_one_laler; j++) {
            adj[V - V_of_one_laler + j - 1][V - 1] = dist(gen);
        }

        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                file << adj[i][j] << ", ";
            }
            file << "\n";
        }
    }
    file.close();

    cout << "File '" << file_name << "' was generated (V = " << V << ")\n";
    return adj;
}
