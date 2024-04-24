#include "../include/graphs/adjacency_matrix_graph.hpp"

AdjacencyMatrixGraph::AdjacencyMatrixGraph(int numVertices) : numVertices(numVertices)
{
    // Inicjalizacja macierzy sąsiedztwa jako pusta macierz o wymiarach numVertices x numVertices
    adjacencyMatrix.resize(numVertices, std::vector<int>(numVertices, 0));
}

void AdjacencyMatrixGraph::add_vertex(int vertex)
{
    numVertices++;
    adjacencyMatrix.resize(numVertices,std::vector<int>(numVertices,0));
    for(int i = 0; i<= numVertices;i++)
    {
        adjacencyMatrix[i].resize(numVertices);
    }
}


void AdjacencyMatrixGraph::add_edge(int vertex_1, int vertex_2, int weight)
{
    // Dodanie krawędzi między wierzchołkami u i v
    adjacencyMatrix[vertex_1-1][vertex_2-1] = weight;
    adjacencyMatrix[vertex_2-1][vertex_1-1] = weight;
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
    int numVertices;
    is >> numVertices;

    // Utwórz nowy obiekt klasy AdjacencyMatrixGraph z wczytaną liczbą wierzchołków
    std::unique_ptr<AdjacencyMatrixGraph> graph = std::make_unique<AdjacencyMatrixGraph>(numVertices);

    // Wczytaj liczbe krawędzi
    int numEdges;
    is >> numEdges;

    // Wczytaj krawędzie i dodaj je do grafu
    for (int i = 0; i < numEdges; ++i) 
    {
        int vertex_1, vertex_2, weight;
        is >> vertex_1 >> vertex_2 >> weight;
        
        // Sprawdzenie, czy wczytano poprawnie wszystkie wartości
        if (is.fail()) {
            // W przypadku niepowodzenia wczytania, ustaw wagę na domyślną wartość, na przykład 1
            weight = 1;
            // Wyczyść flagę błędu strumienia wejściowego
            is.clear();
        }
        
        // Dodaj krawędź do grafu
        graph->add_edge(vertex_1, vertex_2, weight);
    }

    // Zwróć utworzony graf
    return std::move(graph);
}
