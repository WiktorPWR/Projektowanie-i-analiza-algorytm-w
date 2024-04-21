#ifndef GRAPH_HPP_
#define GRAPH_HPP_
#include <vector>
template <typename T>
class Graph
{
  public:
    virtual void add_vertex(T vertex) = 0;//dodanie wierzcholka
    virtual void add_edge(T vertex_1, T vertex_2, T weight) = 0;//dodanie krawedzi
    virtual void remove_vertex(T vertex) = 0;//usuwanie wiercholka
    virtual void remove_edge(T vertex_1, T vertex_2)  = 0;//usuwanie krawedzi
    virtual std::vector<T> get_neighbors(T vertex)  = 0;//Wyswietlenie wszystkich sasiadow danego wezla 
    
    // // TODO: implement all required methods
};

#endif /* GRAPH_HPP_ */
