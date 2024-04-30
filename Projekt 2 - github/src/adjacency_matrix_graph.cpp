#include "../include/graphs/adjacency_matrix_graph.hpp"

AdjacencyMatrixGraph::AdjacencyMatrixGraph(int numVertices) : numVertices(numVertices)
{
    // Inicjalizacja macierzy sąsiedztwa jako pusta macierz o wymiarach numVertices x numVertices
    adjacencyMatrix.resize(numVertices);
    for (int i = 0; i < numVertices; ++i) {
        adjacencyMatrix[i].resize(numVertices, std::make_pair(-1, 0)); // -1 oznacza brak krawędzi
    }
}
int AdjacencyMatrixGraph::graph_size() const
{
    return numVertices;
}

void AdjacencyMatrixGraph::add_vertex(int vertex)
{
    if (vertex < 0)
    {
        std::cerr << "Błąd: Numer wierzchołka nie może być ujemny." << std::endl;
        return;
    }

    if (vertex >= numVertices)
    {
        numVertices = vertex + 1;
        adjacencyMatrix.resize(numVertices);
        for (int i = 0; i < numVertices; ++i)
        {
            adjacencyMatrix[i].resize(numVertices, std::make_pair(-1, 0)); // -1 oznacza brak krawędzi
        }
    }
    else
    {
        std::cerr << "Błąd: Wierzchołek już istnieje." << std::endl;
    }
}

void AdjacencyMatrixGraph::add_edge(int vertex_1, int vertex_2, int weight)
{
    if (vertex_1 < 0 || vertex_1 >= numVertices || vertex_2 < 0 || vertex_2 >= numVertices)
    {
        std::cerr << "Błąd: Nieprawidłowy wierzchołek." << std::endl;
        return;
    }

    if (vertex_1 == vertex_2)
    {
        std::cerr << "Błąd: Pętle nie są obsługiwane." << std::endl;
        return;
    }

    adjacencyMatrix[vertex_1][vertex_2] = std::make_pair(vertex_2, weight);
    adjacencyMatrix[vertex_2][vertex_1] = std::make_pair(vertex_1, weight);
}

int AdjacencyMatrixGraph::has_edge(int vertex_1, int vertex_2) const
{
    return adjacencyMatrix[vertex_1][vertex_2].first != -1;
}

std::vector<std::pair<int, int>> AdjacencyMatrixGraph::getNeighbors(int vertex) const
{
    std::vector<std::pair<int, int>> neighbors;

    for (int v = 0; v < numVertices; ++v)
    {
        if (adjacencyMatrix[vertex][v].first != -1)
        {
            neighbors.push_back(adjacencyMatrix[vertex][v]);
        }
    }

    return neighbors;
}

void AdjacencyMatrixGraph::print_graph() const
{
    for (int i = 0; i < numVertices; ++i)
    {
        std::cout << "Vertex " << i << " -> ";
        for (int j = 0; j < numVertices; ++j)
        {
            if (adjacencyMatrix[i][j].first != -1)
            {
                std::cout << "(" << adjacencyMatrix[i][j].first << ", " << adjacencyMatrix[i][j].second << ") ";
            }
        }
        std::cout << std::endl;
    }
}

std::unique_ptr<Graph> AdjacencyMatrixGraph::createGraph(std::istream& is)
{
    int numVertices, numEdges;
    is >> numVertices;
    if (is.fail()) {
        std::cerr << "Błąd odczytu liczby wierzchołków." << std::endl;
        return nullptr;
    }

    std::unique_ptr<AdjacencyMatrixGraph> graph = std::make_unique<AdjacencyMatrixGraph>(numVertices);
    is >> numEdges;
    if (is.fail()) {
        std::cerr << "Błąd odczytu liczby krawędzi." << std::endl;
        return nullptr;
    }

    for (int i = 0; i < numEdges; ++i) {
        int vertex_1, vertex_2, weight;
        is >> vertex_1 >> vertex_2 >> weight;
        if (is.fail()) {
            std::cerr << "Błąd odczytu danych krawędzi." << std::endl;
            return nullptr;
        }
        graph->add_edge(vertex_1, vertex_2, weight);
    }

    return std::move(graph);
}
