#include "graphs/adjacency_matrix_graph.hpp"

AdjacencyMatrixGraph::AdjacencyMatrixGraph(int numVertices) : numVertices(numVertices)
{
    // Inicjalizacja macierzy sąsiedztwa jako pusta macierz o wymiarach numVertices x numVertices
    adjacencyMatrix.resize(numVertices, std::vector<int>(numVertices, 0));
}

void AdjacencyMatrixGraph::add_vertex(int vertex)
{
    numVertices++;
    adjacencyMatrix.resize(numVertices,std::vector<int>(0));
    for(int i = 0; i<= numVertices;i++)
    {
        adjacencyMatrix[i].resize(numVertices);
    }
}

void AdjacencyMatrixGraph::add_edge(int vertex_1, int vertex_2, int weight)
{
    // Dodanie krawędzi między wierzchołkami u i v
    adjacencyMatrix[vertex_1][vertex_2] = weight;
    adjacencyMatrix[vertex_2][vertex_1] = weight;
}

int AdjacencyMatrixGraph::has_edge(int vertex_1, int vertex_2) const
{
    // Sprawdzenie, czy istnieje krawędź między wierzchołkami u i v
    return adjacencyMatrix[vertex_1][vertex_2];
}

std::vector<int> AdjacencyMatrixGraph::getNeighbors(int vertex) const
{
    std::vector<int> neighbors;

    // Przejście przez wszystkie wierzchołki i sprawdzenie, czy istnieje krawędź między u i danym wierzchołkiem
    for (int v = 0; v < numVertices; ++v)
    {
        if (adjacencyMatrix[vertex][v])
        {
            neighbors.push_back(v);
        }
    }

    return neighbors;
}

std::unique_ptr<Graph> AdjacencyMatrixGraph::createGraph(std::istream& is)
{
    // Tutaj możesz zaimplementować logikę wczytywania danych z strumienia wejściowego is
    // Następnie stwórz nowy obiekt klasy AdjacencyMatrixGraph i zwróć go
    // Na razie zwracamy pusty graf
    return std::make_unique<AdjacencyMatrixGraph>(0);
}
