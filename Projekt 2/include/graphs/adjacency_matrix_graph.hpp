#ifndef ADJACENCY_MATRIX_GRAPH_HPP_
#define ADJACENCY_MATRIX_GRAPH_HPP_

#include <memory>
#include <vector>
#include "graphs/graph.hpp"
template <typename T>

class AdjacencyMatrixGraph : public Graph
{
  private:
    std::vector<std::vector<T>> matrix;
    
  public:
    // TODO: implement
    void add_vertex(T vectex)
    {
      matrix.insert(matrix.begin()+ vectex,0);
    }
    void add_edge(T vectex_1, T vectex_2)
    {
      matrix.insert(matrix.begin()+vectex_1,);
    }

    static std::unique_ptr<Graph> createGraph(std::istream& is);
};

#endif /* ADJACENCY_MATRIX_GRAPH_HPP_ */
