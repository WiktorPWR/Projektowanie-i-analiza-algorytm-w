#ifndef ADJACENCY_MATRIX_GRAPH_HPP_
#define ADJACENCY_MATRIX_GRAPH_HPP_

#include <memory>
#include <iostream>

#include "../graphs/graph.hpp"
class AdjacencyMatrixGraph : public Graph
{
private:
    std::vector<std::vector<std::pair<int,int>>> adjacencyMatrix; // Macierz sąsiedztwa
    int numVertices; // Liczba wierzchołków

public:
    // Konstruktor
    AdjacencyMatrixGraph(int numVertices);

    // Metody implementowane z klasy bazowej Graph
    void add_vertex(int vertex) override;

    void add_edge(int vertex_1, int vertex_2, int weight) override;

    int has_edge(int vertex_1, int vertex_2) const override;

    std::vector<std::pair<int,int>> getNeighbors(int vertex) const override;

    void print_graph() const override;
    
    // Metoda statyczna do tworzenia grafu
    static std::unique_ptr<Graph> createGraph(std::istream& is);
};

#endif /* ADJACENCY_MATRIX_GRAPH_HPP_ */
