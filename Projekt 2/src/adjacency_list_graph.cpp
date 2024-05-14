#include "../include/graphs/adjacency_list_graph.hpp"  // Dołącz plik nagłówkowy zawierający deklarację klasy AdjacencyListGraph
#include <iostream>  // Dołącz bibliotekę obsługi strumieni wejścia/wyjścia
#include <algorithm>  // Dołącz bibliotekę algorytmów

AdjacencyListGraph::AdjacencyListGraph(int numVertices) : numVertices(numVertices) // Konstruktor klasy AdjacencyListGraph, inicjalizuje numVertices oraz tworzy macierz sąsiedztwa o rozmiarze numVertices x numVertices
{
    adjacency_list.resize(numVertices);  // Inicjalizacja listy sąsiedztwa dla każdego wierzchołka grafu
}

void AdjacencyListGraph::clear()  // Funkcja do usuwania wszystkich krawędzi z grafu
{
    for (auto& edges : adjacency_list) {  // Iteracja przez listę sąsiedztwa dla każdego wierzchołka grafu
        edges.clear();  // Usunięcie wszystkich krawędzi dla danego wierzchołka
    }
}

int AdjacencyListGraph::graph_size() const  // Funkcja zwracająca liczbę wierzchołków w grafie
{
    return numVertices;  // Zwraca wartość zmiennej numVertices
}

int AdjacencyListGraph::graph_edges() const  // Funkcja zwracająca liczbę krawędzi w grafie
{
    return numEdges;  // Zwraca wartość zmiennej numEdges
}

void AdjacencyListGraph::add_vertex(int vertex) {  // Funkcja do dodawania nowego wierzchołka do grafu
    if (vertex < 0) {  // Sprawdzenie, czy numer wierzchołka jest dodatni
        std::cerr << "Błąd: Numer wierzchołka nie może być ujemny." << std::endl;  // Wypisanie błędu, jeśli numer wierzchołka jest ujemny
        return;  // Zakończenie funkcji
    }

    if (vertex >= numVertices) {  // Sprawdzenie, czy numer wierzchołka jest większy lub równy liczbie wierzchołków w grafie
        numVertices = vertex + 1;  // Aktualizacja liczby wierzchołków w grafie
        adjacency_list.resize(numVertices);  // Zmiana rozmiaru listy sąsiedztwa, aby pomieścić nowy wierzchołek
    } else {  // W przeciwnym razie, jeśli wierzchołek już istnieje
        std::cerr << "Błąd: Wierzchołek już istnieje." << std::endl;  // Wypisanie błędu
    }
}



void AdjacencyListGraph::add_edge(int vertex_1, int vertex_2, int weight)  // Funkcja do dodawania nowej krawędzi do grafu
{
    if (vertex_1 < 0 || vertex_1 >= adjacency_list.size() || vertex_2 < 0 || vertex_2 >= adjacency_list.size()) {  // Sprawdzenie poprawności numerów wierzchołków
        std::cerr << "Błąd: Nieprawidłowy wierzchołek." << std::endl;  // Wypisanie błędu, jeśli numery wierzchołków są niepoprawne
        return;  // Zakończenie funkcji
    }

    if (vertex_1 == vertex_2) {  // Sprawdzenie, czy to nie jest pętla
        std::cerr << "Błąd: Pętle nie są obsługiwane." << std::endl;  // Wypisanie błędu, jeśli próbujemy dodać pętlę
        return;  // Zakończenie funkcji
    }

    adjacency_list[vertex_1].push_back(std::make_pair(vertex_2, weight));  // Dodanie krawędzi od wierzchołka 1 do wierzchołka 2
    adjacency_list[vertex_2].push_back(std::make_pair(vertex_1, weight));  // Dodanie krawędzi od wierzchołka 2 do wierzchołka 1 (graf nieskierowany)
    numEdges++;  // Zwiększenie licznika krawędzi
}


void AdjacencyListGraph::vertex() const  // Funkcja do wyświetlania wierzchołków grafu
{
    std::cout << "Vertices:" << std::endl;  // Wypisanie nagłówka
    for (int i = 0; i < numVertices; ++i)  // Iteracja przez wszystkie wierzchołki
    {
        std::cout << i << std::endl;  // Wyświetlenie numeru wierzchołka
    }
}

void AdjacencyListGraph::edges() const  // Funkcja do wyświetlania krawędzi grafu
{
    std::cout << "Edges:" << std::endl;  // Wypisanie nagłówka
    for (int i = 0; i < numVertices; ++i)  // Iteracja przez wszystkie wierzchołki
    {
        for (const auto &edge : adjacency_list[i])  // Iteracja przez wszystkie krawędzie dla danego wierzchołka
        {
            std::cout << "(" << i << ", " << edge.first << ") -> " << edge.second << std::endl;  // Wyświetlenie krawędzi
        }
    }
}

void AdjacencyListGraph::remove_edge(int vertex_1, int vertex_2)  // Funkcja do usuwania krawędzi z grafu
{
    if (vertex_1 < 0 || vertex_1 >= adjacency_list.size() || vertex_2 < 0 || vertex_2 >= adjacency_list.size())  // Sprawdzenie poprawności numerów wierzchołków
    {
        std::cerr << "Błąd: Nieprawidłowy wierzchołek." << std::endl;  // Wypisanie błędu, jeśli numery wierzchołków są niepoprawne
        return;  // Zakończenie funkcji
    }

    auto it = std::find_if(adjacency_list[vertex_1].begin(), adjacency_list[vertex_1].end(),
                           [vertex_2](const std::pair<int, int> &p) { return p.first == vertex_2; });  // Wyszukanie krawędzi między vertex_1 i vertex_2

    if (it != adjacency_list[vertex_1].end())  // Jeśli krawędź została znaleziona
    {
        adjacency_list[vertex_1].erase(it);  // Usunięcie krawędzi
    }

    it = std::find_if(adjacency_list[vertex_2].begin(), adjacency_list[vertex_2].end(),
                      [vertex_1](const std::pair<int, int> &p) { return p.first == vertex_1; });  // Wyszukanie krawędzi między vertex_2 i vertex_1

    if (it != adjacency_list[vertex_2].end())  // Jeśli krawędź została znaleziona
    {
        adjacency_list[vertex_2].erase(it);  // Usunięcie krawędzi
    }
    numEdges--;  // Zmniejszenie licznika krawędzi
}

void AdjacencyListGraph::remove_vertex(int vertex)  // Funkcja do usuwania wierzchołka z grafu
{
    if (vertex < 0 || vertex >= numVertices)  // Sprawdzenie poprawności numeru wierzchołka
    {
        std::cerr << "Błąd: Nieprawidłowy wierzchołek." << std::endl;  // Wypisanie błędu, jeśli numer wierzchołka jest niepoprawny
        return;  // Zakończenie funkcji
    }

    // Usunięcie wszystkich krawędzi związanych z usuwanym wierzchołkiem
    for (auto &edges : adjacency_list)  // Iteracja przez listę sąsiedztwa dla każdego wierzchołka
    {
        edges.erase(std::remove_if(edges.begin(), edges.end(), [vertex](const std::pair<int, int> &p) { return p.first == vertex; }), edges.end());  // Usunięcie krawędzi prowadzących do usuwanego wierzchołka
    }

    // Usunięcie wierzchołka z listy sąsiedztwa
    adjacency_list.erase(adjacency_list.begin() + vertex);

    numVertices--;  // Zmniejszenie licznika wierzchołków
}


int AdjacencyListGraph::has_edge(int vertex_1, int vertex_2) const  // Funkcja sprawdzająca, czy istnieje krawędź między dwoma wierzchołkami
{
    for (const auto& edge : adjacency_list[vertex_1])  // Iteracja przez krawędzie wierzchołka vertex_1
    {
        if(edge.first == vertex_2)  // Jeśli krawędź prowadzi do wierzchołka vertex_2
        {
            return true;  // Zwróć true
        }
    }
    return false;  // W przeciwnym razie zwróć false
}



std::vector<std::pair<int,int>> AdjacencyListGraph::getNeighbors(int vertex) const  // Funkcja zwracająca listę sąsiedztwa dla danego wierzchołka
{
    return adjacency_list[vertex];  // Zwróć listę sąsiedztwa dla wierzchołka vertex
}

void AdjacencyListGraph::print_graph() const  // Funkcja do wyświetlania grafu
{
    for(int i = 0; i < adjacency_list.size(); i++)  // Iteracja przez wszystkie wierzchołki
    {
        std::cout << i << ": ";  // Wyświetlenie numeru wierzchołka
        for(const auto& edge : adjacency_list[i])  // Iteracja przez krawędzie danego wierzchołka
        {
            std::cout << "(" << edge.first << ", " << edge.second << ")";  // Wyświetlenie krawędzi
        }
        std::cout << std::endl;  // Nowa linia
    }
}



std::unique_ptr<Graph> AdjacencyListGraph::createGraph(std::istream& is)  // Funkcja do tworzenia grafu na podstawie danych z strumienia wejściowego
{
    int numVertices, numEdges;   // Deklaracja zmiennych przechowujących liczbę wierzchołków i krawędzi
    is >> numVertices;   // Wczytanie liczby wierzchołków
    if (is.fail()) {   // Sprawdzenie, czy operacja wczytywania zakończyła się niepowodzeniem
        std::cerr << "Błąd odczytu liczby wierzchołków." << std::endl;   // Wypisanie komunikatu o błędzie
        return nullptr;  // Zwrócenie wskaźnika null
    }

    std::unique_ptr<AdjacencyListGraph> graph = std::make_unique<AdjacencyListGraph>(numVertices);  // Utworzenie obiektu grafu
    graph->adjacency_list.resize(numVertices);  // Zmiana rozmiaru listy sąsiedztwa
    is >> numEdges;  // Wczytanie liczby krawędzi
    if (is.fail()) {  // Sprawdzenie, czy operacja wczytywania zakończyła się niepowodzeniem
        std::cerr << "Błąd odczytu liczby krawędzi." << std::endl;  // Wypisanie komunikatu o błędzie
        return nullptr;  // Zwrócenie wskaźnika null
    }

    for (int i = 0; i < numEdges; ++i) {  // Pętla wczytująca dane o krawędziach
        int vertex_1, vertex_2, weight;  // Deklaracja zmiennych przechowujących dane o krawędzi
        is >> vertex_1 >> vertex_2 >> weight;  // Wczytanie danych o krawędzi
        if (is.fail()) {  // Sprawdzenie, czy operacja wczytywania zakończyła się niepowodzeniem
            std::cerr << "Błąd odczytu danych krawędzi." << std::endl;  // Wypisanie komunikatu o błędzie
            return nullptr;  // Zwrócenie wskaźnika null
        }
        graph->add_edge(vertex_1, vertex_2, weight);  // Dodanie krawędzi do grafu
    }

    return std::move(graph);  // Zwrócenie wskaźnika do obiektu grafu
}  
