#include <vector>
#include <queue>
#include <algorithm>
#include "../include/graphs/minimum_spanning_tree_algorithms.hpp"

// Struktura reprezentująca podzbiór w algorytmie Kruskala
struct Subset {
    int parent; // Wskaźnik na rodzica w drzewie podzbioru
    int rank;   // Ranga (wysokość) drzewa podzbioru
};

// Funkcja znajdująca korzeń drzewa dla danego wierzchołka w algorytmie Kruskala
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent); // Rekurencyjnie znajduj korzeń
    return subsets[i].parent; // Zwróć korzeń drzewa
}

// Funkcja łącząca dwa podzbiory w algorytmie Kruskala
void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x); // Znajdź korzeń drzewa dla x
    int yroot = find(subsets, y); // Znajdź korzeń drzewa dla y

    // Dołącz krótsze drzewo do dłuższego
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        // Jeśli rangi są równe, dołącz jedno drzewo i zwiększ rangę
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Algorytm Kruskala znajdujący minimalne drzewo rozpinające
void kruskal(Graph& graph, MinimumSpanningTreeResult& result) {
    int V = graph.graph_size(); // Pobierz liczbę wierzchołków w grafie
    std::vector<std::pair<int, std::pair<int, int>>> edges; // Wektor krawędzi w postaci (waga, (wierzchołek_1, wierzchołek_2))

    // Przeglądaj wszystkie wierzchołki i dodawaj ich sąsiadów jako krawędzie
    for (int i = 0; i < V; ++i) {
        std::vector<std::pair<int, int>> neighbors = graph.getNeighbors(i);
        for (const auto& neighbor : neighbors)
            edges.push_back({neighbor.second, {i, neighbor.first}}); // Dodaj krawędź do listy
    }

    std::sort(edges.begin(), edges.end()); // Posortuj krawędzie rosnąco według wagi

    Subset* subsets = new Subset[V]; // Tablica podzbiorów dla każdego wierzchołka
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v; // Ustaw każdy wierzchołek jako korzeń
        subsets[v].rank = 0;    // Ranga drzewa początkowo wynosi 0
    }

    int e = 0; // Licznik dodanych krawędzi
    int i = 0; // Licznik przeglądanych krawędzi
    while (e < V - 1 && i < edges.size()) {
        auto next_edge = edges[i++]; // Wybierz następną krawędź
        int x = find(subsets, next_edge.second.first); // Znajdź korzeń drzewa dla wierzchołka 1 krawędzi
        int y = find(subsets, next_edge.second.second); // Znajdź korzeń drzewa dla wierzchołka 2 krawędzi

        // Jeśli dodanie krawędzi nie utworzy cyklu, dodaj ją do wyniku
        if (x != y) {
            MinimumSpanningEdge edge; // Utwórz krawędź minimalnego drzewa rozpinającego
            edge.v1 = next_edge.second.first;
            edge.v2 = next_edge.second.second;
            edge.weight = next_edge.first;
            result.push_back(edge); // Dodaj krawędź do wyniku
            Union(subsets, x, y); // Połącz drzewa
            ++e; // Zwiększ licznik dodanych krawędzi
        }
    }

    delete[] subsets; // Zwolnij pamięć zaalokowaną dla tablicy podzbiorów
}

// Algorytm Prima znajdujący minimalne drzewo rozpinające
void prim(Graph& graph, MinimumSpanningTreeResult& result) {
    int V = graph.graph_size(); // Pobierz liczbę wierzchołków w grafie
    std::vector<int> parent(V, -1); // Tablica przechowująca rodziców wierzchołków w minimalnym drzewie rozpinającym
    std::vector<int> key(V, INT_MAX); // Tablica przechowująca klucze (wagi) wierzchołków
    std::vector<bool> in_mst(V, false); // Tablica określająca, czy dany wierzchołek jest już w minimalnym drzewie rozpinającym

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq; // Kolejka priorytetowa przechowująca pary (waga, wierzchołek)

    pq.push({0, 0}); // Dodaj wierzchołek startowy do kolejki z wagą 0
    key[0] = 0; // Ustaw wagę wierzchołka startowego na 0

    // Główna pętla algorytmu
    while (!pq.empty()) {
        int u = pq.top().second; // Pobierz wierzchołek o najmniejszym kluczu z kolejki
        pq.pop(); // Usuń ten wierzchołek z kolejki

        in_mst[u] = true; // Oznacz wierzchołek jako przetworzony

        // Przeglądaj sąsiadów wierzchołka u
        std::vector<std::pair<int, int>> neighbors = graph.getNeighbors(u);
        for (const auto& neighbor : neighbors) {
            int v = neighbor.first; // Pobierz wierzchołek sąsiada
            int weight = neighbor.second; // Pobierz wagę krawędzi

            // Jeśli sąsiad nie jest jeszcze w minimalnym drzewie rozpinającym i jego waga jest mniejsza od dotychczasowej, aktualizuj klucz i rodzica
            if (!in_mst[v] && weight < key[v]) {
                key[v] = weight; // Aktualizuj wagę wierzchołka
                parent[v] = u; // Ustaw rodzica wierzchołka
                pq.push({key[v], v}); // Dodaj wierzchołek do kolejki priorytetowej
            }
        }
    }

    // Dodaj krawędzie do wyniku na podstawie tablicy rodziców i wag krawędzi
    for (int i = 1; i < V; ++i) {
        MinimumSpanningEdge edge; // Utwórz krawędź minimalnego drzewa rozpinającego
        edge.v1 = parent[i]; // Pobierz rodzica
        edge.v2 = i; // Aktualny wierzchołek
        edge.weight = key[i]; // Waga krawędzi
        result.push_back(edge); // Dodaj krawędź do wyniku
    }
}
