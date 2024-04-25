#include <iostream>
#include <fstream> // Do obsługi plików

#include "../include/graphs/adjacency_list_graph.hpp"
#include "../src/adjacency_list_graph.cpp"

int main() {
    // Otwórz plik zawierający dane grafu
    std::ifstream inputFile("../sp_data/graph/graphV10D0.5.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Nie mozna otworzyc pliku." << std::endl;
        return 1;
    }

    // Utwórz obiekt grafu za pomocą funkcji createGraph
    std::unique_ptr<Graph> graph = AdjacencyListGraph::createGraph(inputFile);

    // Sprawdź, czy obiekt został poprawnie utworzony
    if (!graph) {
        std::cerr << "Nie udało się utworzyć obiektu grafu." << std::endl;
        return 1;
    }

    graph->print_graph();

    return 0;
}
