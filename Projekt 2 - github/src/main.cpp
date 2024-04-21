
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
    AdjacencyMatrixGraph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_edge(1,2,5);
    graph.add_edge(1,3,3);
    graph.remove_edge(1,2);
    graph.remove_vertex(1);
    graph.add_vertex(1);
    graph.print_matrix();
    return 0;
}
