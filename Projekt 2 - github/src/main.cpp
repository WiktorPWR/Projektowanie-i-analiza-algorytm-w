#include "../include/graphs/minimum_spanning_tree_algorithms.hpp"
#include "../src/adjacency_list_graph.cpp"
#include "../src/minimum_spanning_tree_algorithms.cpp"
#include "../include/graphs/adjacency_list_graph.hpp"
#include "../src/adjacency_matrix_graph.cpp"
#include "../include/graphs/adjacency_matrix_graph.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <algorithm>

int main() {
    std::ifstream inputFile("../mst_data/graph/graphV10D0.5.txt"); // Nazwa pliku wejściowego

    if (!inputFile.is_open()) {
        std::cerr << "Błąd otwierania pliku." << std::endl;
        return 1;
    }

    // Tworzymy obiekt grafu z wykorzystaniem klasy AdjacencyMatrixGraph
    std::unique_ptr<Graph> graph = AdjacencyMatrixGraph::createGraph(inputFile);

    if (!graph) {
        std::cerr << "Błąd tworzenia grafu." << std::endl;
        return 1;
    }

    // Wyświetlamy wczytany graf
    std::cout << "Graf wczytany z pliku input.txt:" << std::endl;
    graph->print_graph();

    inputFile.close();

    // Wywołujemy algorytm Prima
    MinimumSpanningTreeResult primResult;
    prim(*graph, primResult);

    // Wyświetlamy wynik algorytmu Prima
    std::cout << "Wynik algorytmu Prima:" << std::endl;
    for (const auto& edge : primResult) {
        std::cout << edge.vertex_1 << " " << edge.vertex_2 << " " << edge.weight << std::endl;
    }

    // Wywołujemy algorytm Kruskala
    MinimumSpanningTreeResult kruskalResult;
    kruskal(*graph, kruskalResult);

    // Wyświetlamy wynik algorytmu Kruskala
    std::cout << "Wynik algorytmu Kruskala:" << std::endl;
    for (const auto& edge : kruskalResult) {
        std::cout << edge.vertex_1 << " " << edge.vertex_2 << " " << edge.weight << std::endl;
    }

    return 0;
}
