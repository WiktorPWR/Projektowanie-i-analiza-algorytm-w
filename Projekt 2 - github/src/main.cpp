#include <iostream>
#include <fstream> // Do obsługi plików

#include "../include/graphs/adjacency_list_graph.hpp"
#include "../src/adjacency_list_graph.cpp"
#include "../include/graphs/adjacency_matrix_graph.hpp"
#include "../src/adjacency_matrix_graph.cpp"

int main() {
    // Otwórz plik zawierający dane grafu
    std::ifstream inputFile("../sp_data/graph/graphV10D0.5.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Nie mozna otworzyc pliku." << std::endl;
        return 1;
    }

    // Utwórz obiekt grafu za pomocą funkcji createGraph
    //std::unique_ptr<Graph> graph_list = AdjacencyListGraph::createGraph(inputFile);
    std::unique_ptr<Graph> graph_matrix = AdjacencyMatrixGraph::createGraph(inputFile);

    // Sprawdź, czy obiekt został poprawnie utworzony
    if (!graph_matrix) {
        std::cerr << "Nie udało się utworzyć obiektu grafu." << std::endl;
        return 1;
    }

    //graph_list->print_graph();
    std::cout << std::endl;
    graph_matrix->print_graph();

    return 0;
}
