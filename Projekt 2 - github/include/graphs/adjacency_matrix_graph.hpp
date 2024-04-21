#ifndef ADJACENCY_MATRIX_GRAPH_HPP_
#define ADJACENCY_MATRIX_GRAPH_HPP_

#include <memory>
#include <iostream>
#include <vector>
#include "../graphs/graph.hpp"

template <typename T>
class AdjacencyMatrixGraph : public Graph<T> {
private:
    std::vector<std::vector<T>> matrix;
    int vertices;

public:
    AdjacencyMatrixGraph() : vertices(0) {}

    void add_vertex(T vertex) override {
        if (vertex >= vertices) {
            matrix.resize(vertex + 1, std::vector<T>(vertex + 1, 0));
            vertices = vertex + 1;
        }
    }

    void add_edge(T vertex_1, T vertex_2, int weight) override {
        if (vertex_1 < vertices && vertex_2 < vertices) {
            matrix[vertex_1][vertex_2] = weight;
            matrix[vertex_2][vertex_1] = weight;
        }
    }

    void remove_vertex(T vertex) override {
        if (vertex < vertices) {
            matrix.erase(matrix.begin() + vertex);
            for (auto& row : matrix) {
                row.erase(row.begin() + vertex);
            }
            vertices--;
        }
    }

    void remove_edge(T vertex_1, T vertex_2) override {
        if (vertex_1 < vertices && vertex_2 < vertices) {
            matrix[vertex_1][vertex_2] = 0;
            matrix[vertex_2][vertex_1] = 0;
        }
    }

    std::vector<T> get_neighbors(T vertex) override {
        std::vector<T> neighbors;
        if (vertex < vertices) {
            for (T i = 0; i < vertices; ++i) {
                if (matrix[vertex][i] != 0) {
                    neighbors.push_back(i);
                }
            }
        }
        return neighbors;
    }

    void print_matrix() {
        for (const auto& row : matrix) {
            for (T weight : row) {
                std::cout << weight << " ";
            }
            std::cout << std::endl;
        }
    }

    void createGraph(std::istream& is) {
        AdjacencyMatrixGraph graph
        int vertices, edges;
        is >> vertices >> edges; 

        for (int i = 0; i < vertices; ++i) {
            T vertex;
            is >> vertex;
            graph.add_vertex(vertex);
        }

        for (int i = 0; i < edges; ++i) {
            T vertex_1, vertex_2, weight;
            is >> vertex_1 >> vertex_2 >> weight;
            graph.add_edge(vertex_1, vertex_2, weight);
        }

        return graph;
    }
};

#endif /* ADJACENCY_MATRIX_GRAPH_HPP_ */
