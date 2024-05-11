#ifndef ADJACENCY_LIST_GRAPH_HPP_
#define ADJACENCY_LIST_GRAPH_HPP_

#include <memory>

#include "../graphs/graph.hpp"

class AdjacencyListGraph : public Graph
{
  private:
    std::vector<std::vector<std::pair<int,int>>> adjacency_list; // pierwszy numer wierchdzolek a drugi waga
    int numVertices; // Liczba wierzchołków
    int numEdges;

  public:
    // TODO: implement all required methods
    AdjacencyListGraph(int numVertices);

    // Metody implementowane z klasy bazowej Graph
    void clear() override;

    void add_vertex(int vertex) override;

    void add_edge(int vertex_1, int vertex_2, int weight) override;

    void remove_vertex(int vertex) override;

    void remove_edge(int vertex_1, int vertex_2) override;
    
    void vertex() const override;

    void edges() const override;

    int has_edge(int vertex_1, int vertex_2) const override;

    std::vector<std::pair<int,int>> getNeighbors(int vertex) const override;

    void print_graph() const override;

    int graph_size() const override;

    int graph_edges() const override;


    static std::unique_ptr<Graph> createGraph(std::istream& is);
};

#endif /* ADJACENCY_LIST_GRAPH_HPP_ */
