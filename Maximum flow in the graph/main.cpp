#include "Graph.h"
#include "Algorithms.h"
#include "Data.h"
#include <iostream>
#include <chrono>
#include <string>

#include "Relabel_to_front.h"
#include "Holber_Tarjano_by_Smirnova_Anna.h"

#include <conio.h>

using namespace std;

float N = 500;
int k = 50;

void RunAllTests(Algorithm alg, vector<DataUnit> data, string description) {
	cout << description << endl;
	long long time = 0;
	int res = -1;
	int t = 0;
	for (const auto& unit : data) {
		for (int i = 1; i <= N + k; i++) {
			auto start = std::chrono::system_clock::now();
			res = alg(unit.graph, unit.source, unit.sink);
			auto stop = std::chrono::system_clock::now();
			time += i > k ? std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() : 0;
		}
		++t;
		cout << "Graph " << t << " : " << res << " (" << time / N / 1000. << " us)" << endl;
	}	
}

template <typename T>
void RunAllTests(vector<DataUnit> data, string description) {
	cout << description << endl;
	long long time = 0;
	int res = -1;
	int t = 0;
	for (const auto& unit : data) {
		T strc(unit.graph, unit.source, unit.sink);
		for (int i = 1; i <= N + k; i++) {
			auto start = std::chrono::system_clock::now();
			res = strc.max_flow();
			auto stop = std::chrono::system_clock::now();
			time += i > k ? std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() : 0;
		}
		++t;
		cout << "Graph " << t << " : " << res << " (" << time / N / 1000. << " us)" << endl;
	}	
}


int main() {

	vector<DataUnit> data = {
		DataUnit(adj1, 0, 8),
		DataUnit(adj2, 4, 7),
		//DataUnit(adj3, 12, 0), // Samara -> Moscow
		//DataUnit(adj3, 3, 0),  // SPB -> Moscow
		//DataUnit(adj3, 8, 0),  // NN -> Moscow

		// NTWRK
		//DataUnit(5, 10, 1000, 0, 51, "5_10.txt"),
		//DataUnit(10, 10, 1000, 0, 101, "10_10.txt"),
		//DataUnit(15, 10, 1000, 0, 151, "15_10.txt"),
		//DataUnit(20, 10, 1000, 0, 201, "20_10.txt"),
		//DataUnit(5, 20, 1000, 0, 101, "5_20.txt"),
		//DataUnit(10, 20, 1000, 0, 201, "10_20.txt"),
		//DataUnit(15, 20, 1000, 0, 301, "15_20.txt"),
		//DataUnit(20, 20, 1000, 0, 401, "20_20.txt"),
		//DataUnit(5, 30, 1000, 0, 151, "5_30.txt"),
		//DataUnit(10, 30, 1000, 0, 301, "10_30.txt"),
		//DataUnit(15, 30, 1000, 0, 451, "15_30.txt"),
		//DataUnit(20, 30, 1000, 0, 601, "20_30.txt"),
		// V
		//DataUnit("adj_50.txt", 50, 1000, 2, 0, 49),
		//DataUnit("adj_100.txt", 100, 1000, 2, 0, 99),
		//DataUnit("adj_200.txt", 200, 1000, 2, 0, 199),
		//DataUnit("adj_300.txt", 300, 1000, 2, 0, 299),
		//DataUnit("adj_400.txt", 400, 1000, 2, 0, 399),
		//DataUnit("adj_500.txt", 500, 1000, 2, 0, 499),
		//DataUnit("adj_600.txt", 600, 1000, 2, 0, 599),
		//DataUnit("adj_700.txt", 700, 1000, 2, 0, 699),
		//DataUnit("adj_800.txt", 800, 1000, 2, 0, 799),
		//DataUnit("adj_900.txt", 900, 1000, 2, 0, 899),
		//DataUnit("adj_1000.txt", 1000, 1000, 2, 0, 999),
		// CAP
		//DataUnit("adj_100.txt", 100, 1000, 2, 0, 99),
		//DataUnit("adj_100.txt", 100, 10000, 2, 0, 99),
		//DataUnit("adj_100.txt", 100, 100000, 2, 0, 99),
		//DataUnit("adj_100.txt", 100, 1000000, 2, 0, 99),
		//DataUnit("adj_100.txt", 100, 10000000, 2, 0, 99),
		//DataUnit("adj_100.txt", 100, 100000000, 2, 0, 99),
	};

	RunAllTests(ford_fulkerson_method, data, "Ford Fulkerson algorithm (by Shpagin Alexei)");
	RunAllTests(edmonds_karp_algorithm, data, "Edmonds Karp algorithm (by Archakov Ilyas)");
	RunAllTests(dinitz_algorithm, data, "Dinitz algoritm (by Dmitrieva Ekaterina)");
	RunAllTests(dinitz_algorithm, data, "epishov_protalkivanie");
	RunAllTests(dinitz_algorithm, data, "Flow Scaling algorithm (by Caxar)");	
	RunAllTests<HolberTajano>(data, "Golber-Tarjano algorithm (by Smirnova Anna)");
	RunAllTests<RelabelToFront>(data, "Relable to front algorithm (by Kotkov Roman)");	

	return 0;
}
