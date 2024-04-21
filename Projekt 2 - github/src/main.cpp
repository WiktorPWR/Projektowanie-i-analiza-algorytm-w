
#include <iostream>
#include <fstream>
#include <memory>
//#include "../include/graphs/graph.hpp"
#include "../include/graphs/adjacency_matrix_graph.hpp"
int main() {
    std::ifstream inputFile("D:/Pobrane/PiAAGrafy/PiAAGrafy/sp_data/graph/graphV10D0.5.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Nie udało się otworzyć pliku.\n";
        return 1;
    }

    

    return 0;
}
