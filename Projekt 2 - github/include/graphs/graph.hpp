#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <vector>

class Graph
{
public:

    virtual void clear() = 0;
    virtual void add_vertex(int vertex) = 0;
    virtual void add_edge(int vertex_1, int vertex_2, int weight) = 0; // Metoda dodająca krawędź
    virtual void remove_vertex(int vertex) = 0;
    virtual void remove_edge(int vertex_1, int vertex_2) = 0;
    virtual void vertex() const = 0;
    virtual void edges() const = 0;
    virtual int has_edge(int vertex_1, int vertex_2) const = 0; // Metoda sprawdzająca istnienie krawędzi
    virtual std::vector<std::pair<int,int>> getNeighbors(int vertex) const = 0;
    virtual void print_graph() const = 0;
    virtual int graph_size() const = 0;
    virtual int graph_edges() const = 0;
};

#endif /* GRAPH_HPP_ */
