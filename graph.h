//
// Created by Jakub Strawa on 11/19/20.
//

#include <vector>

#ifndef PATHFINDING_A_GRAPH_H
#define PATHFINDING_A_GRAPH_H

#endif //PATHFINDING_A_GRAPH_H

//Wczytywanie grafu z pliku txt
void readGraph(int &startPoint, int &finishPoint, std::vector<std::tuple<int, int, int>> &graph, std::string path);

//sortowanie wierzchołków
void sortGraph(std::vector<std::tuple<int, int, int>> &graph);

//Usuwanie duplikatów krawędzi między wierzchołkami
void deleteDuplicatedVertices(std::vector<std::tuple<int, int, int>> &graph);

//Wypisywanie wszystkich wierzchołków grafu
void printAllVertices(std::vector<std::tuple<int, int, int>> &graph, std::vector<int> &vertices);

//Sprawdzenie warunku czy wierzchołki w grafie są kolejnymi liczbami naturalnymi >0
bool checkVertices(std::vector<int> &vertices);

//Utworzenie macierzy sąsiedztwa dla grafu
void createAdjacencyMatrix(std::vector<std::tuple<int, int, int>> &graph, std::vector<int> &vertices, std::vector<int> &matrix);