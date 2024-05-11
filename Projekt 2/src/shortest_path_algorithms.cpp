#include "../include/graphs/shortest_path_algorithms.hpp"
#include <vector>
#include <limits>
#include <iostream>
#include "../include/graphs/graph.hpp"

void dijkstra(Graph& graph, int sourceIndex, ShortestPathResult& result)
{
    int numVertices = graph.graph_size();

    // Inicjalizacja tablicy odległości
    std::vector<int> distance(numVertices, std::numeric_limits<int>::max());
    distance[sourceIndex] = 0;

    // Tablica przechowująca informację o odwiedzonych wierzchołkach
    std::vector<bool> visited(numVertices, false);

    // Pętla główna algorytmu Dijkstry
    for (int count = 0; count < numVertices - 1; ++count) {
        int minDistance = std::numeric_limits<int>::max();
        int minIndex = -1;

        // Znajdź wierzchołek o najmniejszej odległości
        for (int v = 0; v < numVertices; ++v) {
            if (!visited[v] && distance[v] <= minDistance) {
                minDistance = distance[v];
                minIndex = v;
            }
        }

        // Oznacz wierzchołek jako odwiedzony
        visited[minIndex] = true;

        // Zaktualizuj odległości do sąsiadów wybranego wierzchołka
        for (int v = 0; v < numVertices; ++v) {
            if (!visited[v] && graph.has_edge(minIndex, v)) {
                int weight = graph.getNeighbors(minIndex)[v].second;
                if (distance[minIndex] != std::numeric_limits<int>::max() && distance[minIndex] + weight < distance[v]) {
                    distance[v] = distance[minIndex] + weight;
                }
            }
        }
    }

    // Zapisz odległości do wynikowej struktury
    for (int i = 0; i < numVertices; ++i) {
        result[i] = std::make_pair(distance[i], std::vector<int>()); // Przechowujemy odległość jako pierwszy element pary, a ścieżkę jako drugi
    }
}

bool bellmanFord(Graph& graph, int sourceIndex, ShortestPathResult& result)
{
    int numVertices = graph.graph_size();

    // Inicjalizacja tablicy odległości
    std::vector<int> distance(numVertices, std::numeric_limits<int>::max());
    distance[sourceIndex] = 0;

    // Pętla relaksacji krawędzi
    for (int i = 0; i < numVertices - 1; ++i) {
        for (int u = 0; u < numVertices; ++u) {
            for (int v = 0; v < numVertices; ++v) {
                if (graph.has_edge(u, v)) {
                    int weight = graph.getNeighbors(u)[v].second;
                    if (distance[u] != std::numeric_limits<int>::max() && distance[u] + weight < distance[v]) {
                        distance[v] = distance[u] + weight;
                    }
                }
            }
        }
    }

    // Sprawdzenie obecności ujemnych cykli
    for (int u = 0; u < numVertices; ++u) {
        for (int v = 0; v < numVertices; ++v) {
            if (graph.has_edge(u, v)) {
                int weight = graph.getNeighbors(u)[v].second;
                if (distance[u] != std::numeric_limits<int>::max() && distance[u] + weight < distance[v]) {
                    return false; // Wykryto ujemny cykl
                }
            }
        }
    }

    // Zapisz odległości do wynikowej struktury
    for (int i = 0; i < numVertices; ++i) {
        result[i] = std::make_pair(distance[i], std::vector<int>()); // Przechowujemy odległość jako pierwszy element pary, a ścieżkę jako drugi
    }

    return true;
}
