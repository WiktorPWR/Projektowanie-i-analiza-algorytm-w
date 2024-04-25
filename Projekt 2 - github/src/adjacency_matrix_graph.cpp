
#include "../include/graphs/adjacency_matrix_graph.hpp"

AdjacencyMatrixGraph::AdjacencyMatrixGraph(int numVertices) : numVertices(numVertices)
{
    // Inicjalizacja macierzy sąsiedztwa jako pusta macierz o wymiarach numVertices x numVertices
    adjacencyMatrix.resize(numVertices, std::vector<int>(numVertices, 0));
}

void AdjacencyMatrixGraph::add_vertex(int vertex) {
    if (vertex < 0) {
        std::cerr << "Błąd: Numer wierzchołka nie może być ujemny." << std::endl;
        return;
    }

    if (vertex >= numVertices) {
        numVertices = vertex + 1;
        adjacencyMatrix.resize(numVertices, std::vector<int>(numVertices, 0));
        for (int i = 0; i < numVertices; i++) {
            adjacencyMatrix[i].resize(numVertices);
        }
    } else {
        std::cerr << "Błąd: Wierzchołek już istnieje." << std::endl;
    }
}



void AdjacencyMatrixGraph::add_edge(int vertex_1, int vertex_2, int weight) {
    if (vertex_1 < 0 || vertex_1 >= numVertices || vertex_2 < 0 || vertex_2 >= numVertices) {
        std::cerr << "Błąd: Nieprawidłowy wierzchołek." << std::endl;
        return;
    }

    if (vertex_1 == vertex_2) {
        std::cerr << "Błąd: Pętle nie są obsługiwane." << std::endl;
        return;
    }

    adjacencyMatrix[vertex_1][vertex_2] = weight;
    adjacencyMatrix[vertex_2][vertex_1] = weight;
}


int AdjacencyMatrixGraph::has_edge(int vertex_1, int vertex_2) const
{
    // Sprawdzenie, czy istnieje krawędź między wierzchołkami u i v
    return adjacencyMatrix[vertex_1][vertex_2] != 0;
}

std::vector<int> AdjacencyMatrixGraph::getNeighbors(int vertex) const
{
    std::vector<int> neighbors;

    // Przejście przez wszystkie wierzchołki i sprawdzenie, czy istnieje krawędź między u i danym wierzchołkiem
    for (int v = 0; v < numVertices; ++v)
    {
        if (adjacencyMatrix[vertex][v] != 0)
        {
            neighbors.push_back(v);
        }
    }

    return neighbors;
}

void AdjacencyMatrixGraph::print_graph() const
{
    for (const auto& row : adjacencyMatrix) 
    {
        for (int elem : row) 
        {
            std::cout << elem << " ";
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
        return nullptr; // Przerwanie, jeśli nie udało się wczytać liczby wierzchołków  
    }  

    std::unique_ptr<AdjacencyMatrixGraph> graph = std::make_unique<AdjacencyMatrixGraph>(numVertices);  
    is >> numEdges;  
    if (is.fail()) {  
        std::cerr << "Błąd odczytu liczby krawędzi." << std::endl;  
        return nullptr; // Przerwanie, jeśli nie udało się wczytać liczby krawędzi  
    }  

    for (int i = 0; i < numEdges; ++i) {  
        int vertex_1, vertex_2, weight;  
        is >> vertex_1 >> vertex_2 >> weight;  
        if (is.fail()) {  
            std::cerr << "Błąd odczytu danych krawędzi." << std::endl;  
            return nullptr; // Przerwanie, jeśli nie udało się wczytać danych krawędzi  
        }  
        graph->add_edge(vertex_1, vertex_2, weight);  
    }  

    return std::move(graph);  
}  

