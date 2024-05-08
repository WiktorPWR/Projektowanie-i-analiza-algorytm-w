#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

#define V 5 // liczba wierzchołków w grafie

// Struktura reprezentująca krawędź grafu
struct Edge {
    int to;
    int weight;
};

// Funkcja do implementacji algorytmu Prima
void primMST(vector<vector<Edge>>& graph) {
    // Kolejka priorytetowa przechowująca wierzchołki do odwiedzenia
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    // Wektor do przechowywania kosztu minimalnego drzewa rozpinającego
    vector<int> key(V, INT_MAX);
    
    // Wektor do przechowywania rodzica wierzchołka w minimalnym drzewie rozpinającym
    vector<int> parent(V, -1);
    
    // Wektor przechowujący informacje, czy dany wierzchołek jest już w minimalnym drzewie rozpinającym
    vector<bool> inMST(V, false);
    
    // Wybieramy dowolny wierzchołek startowy (tu wybieramy wierzchołek 0)
    int src = 0;
    key[src] = 0; // Ustawiamy jego klucz na 0
    pq.push({0, src}); // Dodajemy go do kolejki priorytetowej
    
    while (!pq.empty()) {
        int u = pq.top().second; // Wybieramy wierzchołek z najmniejszym kluczem
        pq.pop();
        
        inMST[u] = true; // Oznaczamy, że wierzchołek jest już w minimalnym drzewie rozpinającym
        
        // Przetwarzamy wszystkie sąsiadujące wierzchołki
        for (auto& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;
            // Jeśli v nie jest jeszcze w minimalnym drzewie rozpinającym, a waga krawędzi jest mniejsza niż obecny klucz
            if (!inMST[v] && weight < key[v]) {
                // Aktualizujemy klucz v i ustawiamy v jako rodzica u
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }
    
    // Wypisujemy krawędzie minimalnego drzewa rozpinającego
    for (int i = 1; i < V; i++) {
        cout << "Krawędź " << parent[i] << " - " << i << " waga: " << key[i] << endl;
    }
}

int main() {
    // Przykładowy graf ważony
    vector<vector<Edge>> graph = {
        {{1, 2}, {3, 6}}, // krawędzie wychodzące z wierzchołka 0
        {{0, 2}, {2, 3}, {3, 8}, {4, 5}}, // krawędzie wychodzące z wierzchołka 1
        {{1, 3}, {4, 7}}, // krawędzie wychodzące z wierzchołka 2
        {{0, 6}, {1, 8}, {4, 9}}, // krawędzie wychodzące z wierzchołka 3
        {{1, 5}, {2, 7}, {3, 9}} // krawędzie wychodzące z wierzchołka 4
    };
    
    cout << "Minimalne drzewo rozpinające za pomocą algorytmu Prima:" << endl;
    primMST(graph);

    return 0;
}
