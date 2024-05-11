#define CATCH_CONFIG_MAIN
#define DATA_DIR_PATH "../mst_data"
#include "..\include\graphs\adjacency_list_graph.hpp"
#include "..\include\graphs\adjacency_matrix_graph.hpp"
#include "..\include\graphs\minimum_spanning_tree_algorithms.hpp"
#include "..\src\adjacency_list_graph.cpp"
#include "..\src\adjacency_matrix_graph.cpp"
#include "..\src\minimum_spanning_tree_algorithms.cpp"
#include <filesystem>
#include <fstream>

std::ostream &operator<<(std::ostream &os, const MinimumSpanningEdge& edge){
    os << '{' << std::min(edge.v1, edge.v2) << ", "  << std::max(edge.v1, edge.v2) << ", " << edge.weight<< "} ";
    return os;
}

#include "..\include\catch2\catch.hpp"

using namespace std::string_literals;

const std::filesystem::path dataDirectoryPath{DATA_DIR_PATH};


void readMstResult(std::ifstream &is, MinimumSpanningTreeResult &result) {
    result.clear();

    std::string line;
    while (std::getline(is, line)) {
        std::istringstream iss{line};

        if (!line.empty()) {
            MinimumSpanningEdge edge;

            if (iss >> edge.v1 >> edge.v2 >> edge.weight) {
                result.push_back(edge);
            } else {
                // Handle parsing error
                std::cerr << "Error parsing line: " << line << std::endl;
            }
        }
    }
}


TEST_CASE("Adjacency Matrix Graph -- Kruskal") {
    auto[inputFile, refFile] = GENERATE(std::make_tuple(dataDirectoryPath / "graph" / "graphV10D0.25.txt",
                                                        dataDirectoryPath / "mstResults" / "graphV10D0.25.txt"),
                                        std::make_tuple(dataDirectoryPath / "graph" / "graphV70D0.75.txt",
                                                        dataDirectoryPath / "mstResults" / "graphV70D0.75.txt"),
                                        std::make_tuple(dataDirectoryPath / "graph" / "graphV200D0.5.txt",
                                                        dataDirectoryPath / "mstResults" / "graphV200D0.5.txt"));

    std::ifstream inputStream{inputFile}, refStream{refFile};
    auto graph = AdjacencyMatrixGraph::createGraph(inputStream);

    MinimumSpanningTreeResult result, refResult;

    readMstResult(refStream, refResult);
    std::sort(refResult.begin(),refResult.end());

    kruskal(*graph,result);
    std::sort(result.begin(),result.end());

   

    REQUIRE(result==refResult);
}

TEST_CASE("Adjacency List Graph -- Kruskal")
{
    auto[inputFile, refFile] = GENERATE(std::make_tuple(dataDirectoryPath / "graph" / "graphV10D0.25.txt",
                                                        dataDirectoryPath / "mstResults" / "graphV10D0.25.txt"),
                                        std::make_tuple(dataDirectoryPath / "graph" / "graphV70D0.75.txt",
                                                        dataDirectoryPath / "mstResults" / "graphV70D0.75.txt"),
                                        std::make_tuple(dataDirectoryPath / "graph" / "graphV200D0.5.txt",
                                                        dataDirectoryPath / "mstResults" / "graphV200D0.5.txt"));

    std::ifstream inputStream{inputFile}, refStream{refFile};
    auto graph = AdjacencyListGraph::createGraph(inputStream);

    MinimumSpanningTreeResult result, refResult;

    readMstResult(refStream, refResult);
    std::sort(refResult.begin(),refResult.end());

    kruskal(*graph,result);
    std::sort(result.begin(),result.end());

  

    REQUIRE(result==refResult);
}


TEST_CASE("Adjacency Matrix Graph -- Prim")
{
    auto[inputFile, refFile] = GENERATE(std::make_tuple(dataDirectoryPath / "graph" / "graphV10D0.25.txt",
                                                        dataDirectoryPath / "mstResults" / "graphV10D0.25.txt"),
                                        std::make_tuple(dataDirectoryPath / "graph" / "graphV70D0.75.txt",
                                                        dataDirectoryPath / "mstResults" / "graphV70D0.75.txt"),
                                        std::make_tuple(dataDirectoryPath / "graph" / "graphV200D0.5.txt",
                                                        dataDirectoryPath / "mstResults" / "graphV200D0.5.txt"));

    std::ifstream inputStream{inputFile}, refStream{refFile};
    auto graph = AdjacencyMatrixGraph::createGraph(inputStream);

    MinimumSpanningTreeResult result, refResult;

    readMstResult(refStream, refResult);
    std::sort(refResult.begin(),refResult.end());

    prim(*graph,result);
    std::sort(result.begin(),result.end());

  

    REQUIRE(result==refResult);
}

TEST_CASE("Adjacency List Graph -- Prim")
{
    auto[inputFile, refFile] = GENERATE(std::make_tuple(dataDirectoryPath / "graph" / "graphV10D0.25.txt",
                                                        dataDirectoryPath / "mstResults" / "graphV10D0.25.txt"),
                                        std::make_tuple(dataDirectoryPath / "graph" / "graphV70D0.75.txt",
                                                        dataDirectoryPath / "mstResults" / "graphV70D0.75.txt"),
                                        std::make_tuple(dataDirectoryPath / "graph" / "graphV200D0.5.txt",
                                                        dataDirectoryPath / "mstResults" / "graphV200D0.5.txt"));

    std::ifstream inputStream{inputFile}, refStream{refFile};
    auto graph = AdjacencyListGraph::createGraph(inputStream);

    MinimumSpanningTreeResult result, refResult;

    readMstResult(refStream, refResult);
    std::sort(refResult.begin(),refResult.end());

    prim(*graph,result);
    std::sort(result.begin(),result.end());


    REQUIRE(result==refResult);
}
