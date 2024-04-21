
#include <iostream>
#include <fstream>
#include <memory>
//#include "../include/graphs/graph.hpp"
#include "../include/graphs/adjacency_matrix_graph.hpp"
int main() {
    std::ifstream inputFile("../mst_data/graph/graphV10D0.5.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Nie udało sie otworzyc pliku.\n";
        return 1;
    }
    return 0;
}

/*
#ifndef ADJACENCY_MATRIX_GRAPH_HPP_
#define ADJACENCY_MATRIX_GRAPH_HPP_

#include <memory>
#include <iostream>
#include "../graphs/graph.hpp"
template <typename T>

class AdjacencyMatrixGraph : public Graph<T>
{
  private:
    std::vector<std::vector<T>> matrix;
    int rows;
    int colums;

  public:

    AdjacencyMatrixGraph()
    {
      rows = 0;
      colums = 0;
    }
    
    void add_vertex(T vertex) override
    {
      matrix.push_back(std::vector(colums,0));
      colums++;
      rows++;
      for(int i = 0; i<= rows;i++)
      {
        matrix[i].resize(colums);
      }
    }

    void add_edge(T vertex_1, T vertex_2, int waga) override
    {//dodaj zabezpieczenie przeciwko wartosci 0 bo ona ozancza ze nie ma polaczenia
      matrix[vertex_1-1].at(vertex_2 - 1) = waga;
      matrix[vertex_2-1].at(vertex_1 - 1) = waga;
    }

    void remove_vertex(T vertex) override
    {
      //implementacja usuwania wszystki krawedzi tego wierzcholka
      for(auto& i : matrix[vertex])
      {
        if(matrix[vertex].at(i) != 0)
        {
          //znajdywanie sasiada
          matrix[i].at(vertex) = 0; 
        }
      }
      
      if (vertex >= 1 && vertex <= matrix.size())// usuwanie calego wierzcholka 
      {
        matrix.erase(matrix.begin() + vertex - 1); // Usunięcie odpowiedniego wiersza
        for (auto& row : matrix) 
        {
            row.erase(row.begin() + vertex - 1); // Usunięcie odpowiedniej kolumny z każdego wiersza
        }
      }
      colums--;
      rows--;

    }

    void remove_edge(T vertex_1,T vertex_2) override
    {
      matrix[vertex_1-1][vertex_2-1] = 0;
      matrix[vertex_2-1][vertex_1-1] = 0;
    }

    std::vector<T> get_neighbors(T vertex) override
    {
      std::vector<T> neighbors;
      if (vertex >= 1 && vertex <= matrix.size()) // Sprawdzenie czy wierzchołek istnieje
      {
          for (int i = 0; i < matrix[vertex - 1].size(); ++i) // Iteracja po wierszu macierzy odpowiadającym wierzchołkowi
          {
              if (matrix[vertex - 1][i] != 0) // Jeśli istnieje krawędź
              {
                  neighbors.push_back(i + 1); // Dodanie sąsiada do listy (indeksowanie zaczynając od 1)
              }
          }
      }
      neighbors.push_back(0);
      return neighbors;
    }



    void print_matrix()
    {
      for(const auto& i : matrix)
      {
        for(int j : i)
        {
          std::cout<< j << " ";
        }
        std::cout << std::endl;
      }
    }
    // TODO: implement

};

#endif /* ADJACENCY_MATRIX_GRAPH_HPP_ */

