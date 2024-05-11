#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include "D:\PWR\algorytmy\.git\Projektowanie-i-analiza-algorytm-w\Projekt 2 - github\include\graphs\adjacency_list_graph.hpp"
#include "D:\PWR\algorytmy\.git\Projektowanie-i-analiza-algorytm-w\Projekt 2 - github\include\graphs\adjacency_matrix_graph.hpp"
#include "D:\PWR\algorytmy\.git\Projektowanie-i-analiza-algorytm-w\Projekt 2 - github\include\graphs\minimum_spanning_tree_algorithms.hpp"
#include "D:\PWR\algorytmy\.git\Projektowanie-i-analiza-algorytm-w\Projekt 2 - github\src\adjacency_list_graph.cpp"
#include "D:\PWR\algorytmy\.git\Projektowanie-i-analiza-algorytm-w\Projekt 2 - github\src\adjacency_matrix_graph.cpp"
#include "D:\PWR\algorytmy\.git\Projektowanie-i-analiza-algorytm-w\Projekt 2 - github\src\minimum_spanning_tree_algorithms.cpp"


// Function to test the algorithm on a graph

// Function to generate a random graph with given density
void generateRandomGraph(Graph& graph, double density) {
    int numVertices = graph.graph_size();
    int numEdges = graph.graph_edges();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < numVertices; ++i) {
        for (int j = i + 1; j < numVertices; ++j) {
            if (dis(gen) < density) {
                int weight = std::rand() % 100 + 1; // Random weight between 1 and 100
                graph.add_edge(i, j, weight);
            }
        }
    }
}

double testAlgorithm(void (*algorithm)(Graph&, MinimumSpanningTreeResult&), const std::unique_ptr<Graph>& graph) {
    MinimumSpanningTreeResult result;
    auto start = std::chrono::steady_clock::now();
    algorithm(*graph, result);
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

// Function to run tests for a given graph representation and parameters
void runTests(std::unique_ptr<Graph>& graph, const std::string& representation, int numVertices, double density) {
    std::cout << "Running tests for " << representation << " representation with " << numVertices << " vertices and " << density * 100 << "% density..." << std::endl;
    double totalKruskalTime = 0.0;
    double totalPrimTime = 0.0;
    const int numInstances = 100;

    int numEdges = graph->graph_edges();

    for (int i = 0; i < numInstances; ++i) {
        // Generate a random graph
        generateRandomGraph(*graph, density);

        // Test Kruskal's Algorithm
        totalKruskalTime += testAlgorithm(kruskal, graph);

        // Test Prim's Algorithm
        totalPrimTime += testAlgorithm(prim, graph);

        // Clear the graph for the next instance
        graph->clear();
    }

    // Calculate average times
    double avgKruskalTime = totalKruskalTime / numInstances;
    double avgPrimTime = totalPrimTime / numInstances;

    // Expected complexities
    double kruskalComplexity, primComplexity;


    std::cout << numVertices << " " << numEdges << std::endl;
    if (representation == "adjacency list") {
    kruskalComplexity = (density == 1.0) ? numVertices * numVertices * log(numVertices) : numEdges * log(numVertices);
    primComplexity = numVertices * numVertices * log(numVertices); // Poprawiona złożoność czasowa dla algorytmu Prima
    } else if (representation == "adjacency matrix") {
        kruskalComplexity = numEdges * log(numVertices);
        primComplexity = numVertices * numVertices;
    }


    // Print results
    std::cout << "Average time for Kruskal's Algorithm: " << avgKruskalTime << " ms (Expected: " << kruskalComplexity << " )" << std::endl;
    std::cout << "Average time for Prim's Algorithm: " << avgPrimTime << " ms (Expected: " << primComplexity << " )" << std::endl;
    std::cout << std::endl;
}

int main() {
    // Define the parameters
    std::vector<int> numVerticesList = {10, 50, 100, 500, 1000};
    std::vector<double> densities = {0.25, 0.5, 0.75, 1.0};

    // Run tests for each combination of parameters
    for (int numVertices : numVerticesList) {
        for (double density : densities) {
            std::unique_ptr<Graph> matrixGraph = std::make_unique<AdjacencyMatrixGraph>(numVertices);
            std::unique_ptr<Graph> listGraph = std::make_unique<AdjacencyListGraph>(numVertices);
            runTests(matrixGraph, "adjacency matrix", numVertices, density);
            runTests(listGraph, "adjacency list", numVertices, density);
        }
    }

    return 0;
}
