#include <iostream>
#include <fstream>
#include <memory>
#include "../src/adjacency_matrix_graph.cpp"
int main() {
    // Tworzenie grafu
    std::unique_ptr<Graph> graph = AdjacencyMatrixGraph::createGraph(std::cin);

    // Dodawanie krawędzi
    graph->add_vertex(1);
    graph->add_vertex(2);
    graph->add_vertex(3);
    graph->add_edge(1,2,69);
    graph->print_graph();
    // Pobieranie sąsiadów wierzchołka
    // std::vector<int> neighbors = graph->getNeighbors(1);
    // std::cout << "Neighbors of vertex 1:";
    // for (int neighbor : neighbors) {
    //     std::cout << " " << neighbor;
    // }
    // std::cout << std::endl;

    return 0;
}

