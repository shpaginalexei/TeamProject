#include <iostream>
using namespace std;

#define V 6

// ������� ��� ���������� relabel ��������
void relabel(int u, int height[], int graph[V][V], int* excess)
{
    int minHeight = INT_MAX;

    // ������� ����������� ������ ������� ������
    for (int v = 0; v < V; v++)
    {
        if (graph[u][v] && height[v] < minHeight)
        {
            minHeight = height[v];
        }
    }

    // ��������� ������ �������
    height[u] = minHeight + 1;
}

// ������� ��� ���������� push ��������
void push(int u, int v, int graph[V][V], int* excess, int height[])
{
    int flow = min(excess[u], graph[u][v]);
    excess[u] -= flow;
    excess[v] += flow;
    graph[u][v] -= flow;
    graph[v][u] += flow;
}

// ������� ��� ���������� ������������� ������
int maxFlow(int graph[V][V], int source, int sink)
{
    // ������������� ����������, ������ � ����������� ��������
    int excess[V] = { 0 };
    int height[V] = { 0 };
    height[source] = V; // ������ ���������

    // ������������� ���������� �� ���������
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

    // ���������� ����������
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

    // ������������ ����� ����� ����������, ���������� �� ���������
    return excess[sink];
}

int main()
{
    // �������� ����
    int graph[V][V] =
    {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0} };

    int source = 0; // ��������
    int sink = 5;   // �������

    cout << "������������ �����: " << maxFlow(graph, source, sink) << endl;

    return 0;
}