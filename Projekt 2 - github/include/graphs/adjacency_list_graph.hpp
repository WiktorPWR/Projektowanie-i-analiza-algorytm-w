#ifndef ADJACENCY_LIST_GRAPH_HPP_
#define ADJACENCY_LIST_GRAPH_HPP_

#include <memory>

#include "../graphs/graph.hpp"

class AdjacencyListGraph : public Graph
{
  private:
    std::vector<std::vector<std::pair<int,int>>> adjacency_list; // Macierz sąsiedztwa
    int numVertices; // Liczba wierzchołków

  public:
    // TODO: implement all required methods
    AdjacencyListGraph(int numVertices);

    // Metody implementowane z klasy bazowej Graph
    void add_vertex(int vertex) override;

    void add_edge(int vertex_1, int vertex_2, int weight) override;

    int has_edge(int vertex_1, int vertex_2) const override;

    std::vector<std::pair<int,int>> getNeighbors(int vertex) const ;

    void print_graph() const override;

    static std::unique_ptr<Graph> createGraph(std::istream& is);
};

#endif /* ADJACENCY_LIST_GRAPH_HPP_ */
