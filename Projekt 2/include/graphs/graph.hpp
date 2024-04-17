#ifndef GRAPH_HPP_
#define GRAPH_HPP_
#include <vector>
template <typename T>

class Graph
{
  public:

  template <typename T> 
  virtual void add_vertex() = 0;//dodanie wierzcholka
  virtual void add_edge() = 0;//dodanie krawedzi
  virtual void remove_vertex() = 0;//usuwanie wiercholka
  virtual void remove_edge() = 0;//usuwanie krawedzi
  virtual void check_edge() = 0;//sprawdzenie czy krawedz istnieje
  virtual std::vector<T> get_neighbors() = 0;//Wyswietlenie wszystkich sasiadow danego wezla 
    // TODO: implement all required methods
};

#endif /* GRAPH_HPP_ */
