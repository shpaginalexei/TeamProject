#include <iostream>
using namespace std;

#define V 6

// Функция для выполнения relabel операции
void relabel(int u, int height[], int graph[V][V], int* excess)
{
    int minHeight = INT_MAX;

    // Находим минимальную высоту смежных вершин
    for (int v = 0; v < V; v++)
    {
        if (graph[u][v] && height[v] < minHeight)
        {
            minHeight = height[v];
        }
    }

    // Обновляем высоту вершины
    height[u] = minHeight + 1;
}

// Функция для выполнения push операции
void push(int u, int v, int graph[V][V], int* excess, int height[])
{
    int flow = min(excess[u], graph[u][v]);
    excess[u] -= flow;
    excess[v] += flow;
    graph[u][v] -= flow;
    graph[v][u] += flow;
}

// Функция для вычисления максимального потока
int maxFlow(int graph[V][V], int source, int sink)
{
    // Инициализация предпотока, высоты и избыточного значения
    int excess[V] = { 0 };
    int height[V] = { 0 };
    height[source] = V; // Высота источника

    // Инициализация предпотока из источника
    for (int v = 0; v < V; v++)
    {
        if (graph[source][v])
        {
            excess[v] = graph[source][v];
            excess[source] -= graph[source][v];
            graph[source][v] = 0;
            graph[v][source] = graph[source][v];
        }
    }

    // Построение предпотока
    while (true)
    {
        bool found = false;
        for (int u = 0; u < V; u++)
        {
            if (u != source && u != sink && excess[u] > 0)
            {
                int v;
                for (v = 0; v < V; v++)
                {
                    if (graph[u][v] && height[u] == height[v] + 1)
                    {
                        found = true;
                        push(u, v, graph, excess, height);
                        break;
                    }
                }
                if (found)
                {
                    break;
                }
            }
        }
        if (!found)
        {
            break;
        }
    }

    // Максимальный поток равен предпотоку, исходящему из источника
    return excess[sink];
}

int main()
{
    // Исходный граф
    int graph[V][V] =
    {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0} };

    int source = 0; // Источник
    int sink = 5;   // Сточник

    cout << "Максимальный поток: " << maxFlow(graph, source, sink) << endl;

    return 0;
}