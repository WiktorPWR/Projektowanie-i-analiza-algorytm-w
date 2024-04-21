
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
    AdjacencyMatrixGraph graph;
    

    return 0;
}
