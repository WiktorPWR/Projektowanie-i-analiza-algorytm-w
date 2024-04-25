#include "../include/graphs/adjacency_list_graph.hpp"
#include <iostream>


AdjacencyListGraph::AdjacencyListGraph(int numVertices) : numVertices(numVertices)
{
    // Inicjalizacja macierzy sąsiedztwa jako pusta macierz o wymiarach numVertices x numVertices
    adjacency_list.resize(numVertices);
}

void AdjacencyListGraph::add_vertex(int vertex) {
    if (vertex < 0) {
        std::cerr << "Błąd: Numer wierzchołka nie może być ujemny." << std::endl;
        return;
    }

    if (vertex >= numVertices) {
        numVertices = vertex + 1;
        adjacency_list.resize(numVertices);
    } else {
        std::cerr << "Błąd: Wierzchołek już istnieje." << std::endl;
    }
}



void AdjacencyListGraph::add_edge(int vertex_1, int vertex_2, int weight)
 {
    if (vertex_1 < 0 || vertex_1 >= adjacency_list.size() || vertex_2 < 0 || vertex_2 >= adjacency_list.size()) {
        std::cerr << "Błąd: Nieprawidłowy wierzchołek." << std::endl;
        return;
    }

    if (vertex_1 == vertex_2) {
        std::cerr << "Błąd: Pętle nie są obsługiwane." << std::endl;
        return;
    }

    adjacency_list[vertex_1].push_back(std::make_pair(vertex_2, weight));
    adjacency_list[vertex_2].push_back(std::make_pair(vertex_1, weight));
}


int AdjacencyListGraph::has_edge(int vertex_1, int vertex_2) const
{
    for (const auto& edge : adjacency_list[vertex_1])
    {
        if(edge.first == vertex_2)
        {
            return true;
        }
    }
    return false;
}

std::vector<std::pair<int,int>> AdjacencyListGraph::getNeighbors(int vertex) const
{
    return adjacency_list[vertex];
}

void AdjacencyListGraph::print_graph() const 
{
    for(int i = 0; i < adjacency_list.size(); i++) 
    {
        std::cout << i << ": ";
        for(const auto& edge : adjacency_list[i]) 
        {
            std::cout << "(" << edge.first << ", " << edge.second << ")";
        }
        std::cout << std::endl;
    }
}



std::unique_ptr<Graph> AdjacencyListGraph::createGraph(std::istream& is)
{
    int numVertices, numEdges;  
    is >> numVertices;  
    if (is.fail()) {  
        std::cerr << "Błąd odczytu liczby wierzchołków." << std::endl;  
        return nullptr; // Przerwanie, jeśli nie udało się wczytać liczby wierzchołków  
    }  

    std::unique_ptr<AdjacencyListGraph> graph = std::make_unique<AdjacencyListGraph>(numVertices); 
    graph->adjacency_list.resize(numVertices); 
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
