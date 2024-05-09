#include <iostream>
#include <fstream>
#include <random>
#include <sstream>
#include <array>
#include <iomanip> // Dodatkowa biblioteka potrzebna do formatowania liczby zmiennoprzecinkowej

class GraphGenerator {
private:
    std::random_device rd;
    std::mt19937 gen;
public:
    GraphGenerator() : gen(rd()) {}

    void generateGraph(int numVertices, double density, const std::string& folderPath) {
        // Formatowanie gęstości grafu do dwóch miejsc po przecinku
        std::ostringstream densityStream;
        densityStream << std::fixed << std::setprecision(2) << density;
        std::string formattedDensity = densityStream.str();

        std::ostringstream filenameStream;
        filenameStream << folderPath << "/graph_density_" << formattedDensity.substr(0, 4) << "_vertices_" << numVertices << ".txt";
        std::string filename = filenameStream.str();

        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return;
        }

        int numEdges = static_cast<int>(density * numVertices * (numVertices - 1) / 2);

        file << numVertices << " " << numEdges << std::endl;

        std::uniform_int_distribution<> disWeight(1, 100);

        for (int i = 0; i < numVertices; ++i) {
            for (int j = i + 1; j < numVertices; ++j) {
                if (file && numEdges > 0) {
                    int weight = disWeight(gen);
                    file << i << " " << j << " " << weight << std::endl;
                    file << j << " " << i << " " << weight << std::endl;
                    numEdges--;
                }
            }
        }

        file.close();
        std::cout << "Graph generated and saved to: " << filename << std::endl;
    }
};

int main() {
    GraphGenerator generator;

    int number_of_elements[] = {10, 50, 100, 500, 1000};
    float density[] = {0.25, 0.50, 0.75, 1.00};
    std::string baseFolderPath = "D:/Grafy_pliki";

    for(int iteration=0;iteration<=100;iteration++)
    {
        for (int i : number_of_elements) {
            for (float j : density) {
                std::string number_of_elements_folder = baseFolderPath + "/" + std::to_string(i); // Ścieżka do podfolderu
                std::string density_folder = number_of_elements_folder + "/" + std::to_string(j);
                std::string folderPath = density_folder;
                generator.generateGraph(i, j, folderPath);
            }
        }
    }

    return 0;
}
