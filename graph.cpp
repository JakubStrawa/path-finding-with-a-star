//
// Created by Jakub Strawa on 11/19/20.
//

#include "graph.h"
#include <vector>
#include <tuple>
#include <fstream>
#include <algorithm>


void readGraph(int &startPoint, int &finishPoint, std::vector<std::tuple<int, int, int>> &graph, std::string path){
    std::vector<int> vec = {-1,-1,-1};
    std::ifstream myfile (path);
    std::string line;
    std::cout << path;
    //wczytywanie grafu i punktów A oraz B
    if (myfile.is_open()) {

        std::cout << "File opened!" << '\n';
        int spacePos1 = 0, spacePos2 = 0;
        while (getline(myfile, line)) {
            if (line.length() == 5) {
                vec[0] = line[0] - '0';
                vec[1] = line[2] - '0';
                vec[2] = line[4] - '0';

                graph.emplace_back(vec[0], vec[1], vec[2]);
                std::cout << line << "/" << vec[0] << "/" << vec[1] << "/" << vec[2] << '\n';
            } else if (line.length() > 5){
                for (int i = 0; i < line.length()-1; i++) {
                    if (!isdigit(line[i])) {
                        if (spacePos1 == 0) {
                            spacePos1 = i;
                        } else {
                            spacePos2 = i;
                        }
                    }
                }
                std::cout << spacePos1 << " " << spacePos2 << std::endl;
                std::string str1 = line.substr(0,spacePos1);
                std::string str2 = line.substr(spacePos1 + 1, spacePos2 - spacePos1 - 1);
                std::string str3 = line.substr(spacePos2, line.length() - spacePos2);
                vec[0] = std::atoi(str1.c_str());
                vec[1] = std::atoi(str2.c_str());
                vec[2] = std::atoi(str3.c_str());
                graph.emplace_back(vec[0], vec[1], vec[2]);
                spacePos1 = 0;
                spacePos2 = 0;
                std::cout << line << "/" << vec[0] << "/" << vec[1] << "/" << vec[2] << '\n';
            } else {
                if (line[0] == 'A') {
                    std::string str1 = line.substr(2, line.length() - 2);
                    startPoint = std::atoi(str1.c_str());
                }
                else if (line[0] == 'B') {
                    std::string str1 = line.substr(2, line.length() - 2);
                    finishPoint = std::atoi(str1.c_str());
                }
            }
        }
        myfile.close();
        std::cout << "from: " << startPoint << " to: " << finishPoint << '\n';
    }
    std::cout << graph.size() << '\n';
}

void sortGraph(std::vector<std::tuple<int, int, int>> &graph){
    //sortowanie wierzchołków
    std::sort(graph.begin(), graph.end(), [](std::tuple<int,int,int> a, std::tuple<int,int,int> b) -> bool
    {
        if (std::get<0>(a) == std::get<0>(b)) {
            return std::get<1>(a) < std::get<1>(b);
        } else {
            return std::get<0>(a) < std::get<0>(b);
        }
    });
}

void deleteDuplicatedVertices(std::vector<std::tuple<int, int, int>> &graph){
    //usuwanie duplikatów krawędzi grafu
    for (int i = 0; i < graph.size(); i++){
        if (i < 0){
            i++;
        }
        if (std::get<0>(graph[i]) == std::get<1>(graph[i])){
            graph.erase(std::find(graph.begin(), graph.end(), graph[i]));
            i--;
        } else if (std::get<0>(graph[i]) == std::get<0>(graph[i+1]) && std::get<1>(graph[i]) == std::get<1>(graph[i+1])){
            graph.erase(std::find(graph.begin(), graph.end(), graph[i+1]));
            i--;
        }
    }
}

void printAllVertices(std::vector<std::tuple<int, int, int>> &graph, std::vector<int> &vertices){
    //wypisywanie wszystkich wierzchołków
    for (auto &v : graph){
        if (std::find(vertices.begin(), vertices.end(), std::get<0>(v)) != vertices.end() && !vertices.empty()){

        } else {
            vertices.push_back(std::get<0>(v));
        }

        if (std::find(vertices.begin(), vertices.end(), std::get<1>(v)) != vertices.end()){

        } else {
            vertices.push_back(std::get<1>(v));
        }
    }
}

bool checkVertices(std::vector<int> &vertices){
    //sortowanie wektora wierzchołków
    std::sort(vertices.begin(), vertices.end(), [](int a, int b) -> bool
    {
        return a < b;
    });

    std::cout << "Vertices: ";

    //sprawdzenie czy wierzchołki są kolejnymi liczbami naturalnymi >0
    int i = 1;
    for (auto v : vertices){
        std::cout << v << " ";
        if (v == i){
            i++;
        } else {
            return false;
        }
    }
    std::cout <<  '\n';
    return true;
}

void createAdjacencyMatrix(std::vector<std::tuple<int, int, int>> &graph, std::vector<int> &vertices, std::vector<int> &matrix){
    //utworzenie macierzy sąsiedztwa
    int verticesAmount = vertices.size();
    for (int x = 0; x < verticesAmount*verticesAmount; x++){
        matrix.push_back(INF);
    }

    for (auto &v : graph){
        matrix[(std::get<0>(v)-1)*verticesAmount + (std::get<1>(v)-1)] = std::get<2>(v);
    }

    //wypisanie macierzy sąsiedztwa
    for (int i = 0; i < verticesAmount; i++) {
        for (int j = 0; j < verticesAmount; j++) {
            std::cout.width(10);
            std::cout << matrix[i*verticesAmount + j] << "\t";
        }
        std::cout << '\n';
    }
}