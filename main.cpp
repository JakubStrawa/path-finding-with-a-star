#include <iostream>
#define INF 10000
#include "graph.cpp"
#include "algorithm.cpp"


int main(int argc, const char * argv[]) {
    std::vector<std::tuple<int, int, int>> graph;
    std::vector<int> vertices;
    std::vector<int> matrix;
    int startPoint = 0, finishPoint = 0, verticesAmount = 0;

    std::string graphFilePath = "graph.txt";

    readGraph(startPoint, finishPoint, graph, graphFilePath);

    sortGraph(graph);

    deleteDuplicatedVertices(graph);

    //wyświetlanie grafu
    for (auto v : graph){
        std::cout << std::get<0>(v) << " " << std::get<1>(v) << " " << std::get<2>(v) << '\n';
    }

    printAllVertices(graph, vertices);

    if (!checkVertices(vertices)){
        std::cout << "\n Graph vertices are not consecutive natural numbers! Check again your graph file! \n";
        return 1;
    }

    verticesAmount = vertices.size();

    createAdjacencyMatrix(graph, vertices, matrix);


    //testowanie algorytmów
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Brute-force algorithm: \n" << findPathBruteForce(matrix, startPoint, finishPoint, verticesAmount) << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: "
              << duration.count() << " microseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    std::cout << "Greedy algorithm: \n" << findPathGreedy(startPoint, finishPoint, matrix, verticesAmount) << std::endl;
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: "
              << duration.count() << " microseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    std::cout << "A* algorithm: \n" << findPathAStar(startPoint, finishPoint, matrix, verticesAmount) << std::endl;
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: "
              << duration.count() << " microseconds" << std::endl;

    return 0;
}
