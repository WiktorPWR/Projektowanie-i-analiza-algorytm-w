#include "../include/graphs/minimum_spanning_tree_algorithms.hpp"
#include <algorithm>
#include <memory>
#include <iostream>
struct Connection
{
    int vertex_1;
    int vertex_2;
    int weight;
};
// Struktura reprezentująca zbiór dla algorytmu Kruskala
struct DisjointSets {
    int *parent, *rank;
    int n;

    DisjointSets(int n) {
        this->n = n;
        parent = new int[n+1];
        rank = new int[n+1];

        for (int i = 0; i <= n; ++i) {
            rank[i] = 0;
            parent[i] = i;
        }
    }

    int find(int u) {
        if (u != parent[u])
        {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void merge(int x, int y) {
        x = find(x), y = find(y);

        if (rank[x] > rank[y])
        {
            parent[y] = x;
        }
        else
        {
            parent[x] = y;
        }
        if (rank[x] == rank[y])
        {
            rank[y]++;
        }
    }
};

bool compareStructs(const Connection &a, const Connection &b) 
{
    return a.weight < b.weight;
}

void kruskal(Graph& graph,MinimumSpanningTreeResult& result)
{
    int size = graph.graph_size();
    
    std::vector<Connection> list;

    std::vector<std::pair<int,int>> neighbors; 
    for(int i = 0;i < size;i++)
    {
        neighbors = graph.getNeighbors(i);
        for(const auto& edge: neighbors)
        {
            if(edge.first >= i)
            {
                Connection connection;
                connection.vertex_1 = i;
                connection.vertex_2 = edge.first;
                connection.weight = edge.second;
                list.push_back(connection);
            }   
        }
    }
    //sortowanie
    std::sort(list.begin(), list.end(), compareStructs);
    

    DisjointSets ds(size);
    std::vector<Connection> MST;// minimalne drewo rozpinające
    // Przechodzimy przez wszystkie krawędzie w posortowanej liście
    for (const auto& edge : list) {
        int u = edge.vertex_1;
        int v = edge.vertex_2;

        int set_u = ds.find(u); // Znajdujemy zbiór, do którego należy wierzchołek u
        int set_v = ds.find(v); // Znajdujemy zbiór, do którego należy wierzchołek v

        // Sprawdzamy, czy dodanie krawędzi nie tworzy cyklu
        if (set_u != set_v) {
            MST.push_back(edge); // Dodajemy krawędź do MST
            ds.merge(set_u, set_v); // Łączymy zbiory zawierające wierzchołki u i v
        }
    }
    
    for (const auto& edge : MST) {
    MinimumSpanningEdge mst_edge;
    mst_edge.v1 = edge.vertex_1;
    mst_edge.v2 = edge.vertex_2;
    mst_edge.weight = edge.weight;
    result.push_back(mst_edge);
    }
}

void prim(Graph& graph, MinimumSpanningTreeResult& result)
{
    // TODO: implement
}
