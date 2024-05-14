#ifndef ADJACENCY_MATRIX_GRAPH_HPP_
#define ADJACENCY_MATRIX_GRAPH_HPP_

#include <memory> // Włączamy nagłówek dla inteligentnych wskaźników.
#include <iostream> // Włączamy nagłówek dla strumieni wejścia/wyjścia.

#include "../graphs/graph.hpp" // Włączamy plik nagłówkowy dla klasy bazowej Graph.

class AdjacencyMatrixGraph : public Graph // Deklarujemy klasę dziedziczącą po Graph.
{
private:
    std::vector<std::vector<std::pair<int,int>>> adjacencyMatrix; // Macierz sąsiedztwa przechowująca pary (numer wierzchołka, waga krawędzi).
    int numVertices; // Liczba wierzchołków w grafie.
    int numEdges; // Liczba krawędzi w grafie.

public:
    // Konstruktor
    AdjacencyMatrixGraph(int numVertices);

    // Metody implementowane z klasy bazowej Graph

    // Czyści graf.
    void clear() override;

    // Dodaje wierzchołek do grafu.
    void add_vertex(int vertex) override;

    // Dodaje krawędź do grafu.
    void add_edge(int vertex_1, int vertex_2, int weight) override;

    // Usuwa wierzchołek z grafu.
    void remove_vertex(int vertex) override;

    // Usuwa krawędź z grafu.
    void remove_edge(int vertex_1, int vertex_2) override;

    // Wyświetla wierzchołki grafu.
    void vertex() const override;

    // Wyświetla krawędzie grafu.
    void edges() const override;

    // Sprawdza, czy istnieje krawędź między dwoma wierzchołkami.
    int has_edge(int vertex_1, int vertex_2) const override;

    // Zwraca listę sąsiadów danego wierzchołka w grafie.
    std::vector<std::pair<int,int>> getNeighbors(int vertex) const override;

    // Wyświetla graf.
    void print_graph() const override;

    // Zwraca liczbę wierzchołków w grafie.
    int graph_size() const override;

    // Zwraca liczbę krawędzi w grafie.
    int graph_edges() const override;

    // Metoda statyczna do tworzenia grafu na podstawie strumienia wejściowego.
    static std::unique_ptr<Graph> createGraph(std::istream& is);
};

#endif /* ADJACENCY_MATRIX_GRAPH_HPP_ */
