//
// Created by Jakub Strawa on 11/29/20.
//

#ifndef PATH_FINDING_WITH_A_STAR2_ALGORITHM_H
#define PATH_FINDING_WITH_A_STAR2_ALGORITHM_H

#endif //PATH_FINDING_WITH_A_STAR2_ALGORITHM_H

//Heurystyka h(), która określa liczbę krawędzi pomiędzy wszystkimi wierzchołkami w grafie, a wierzchołkiem końcowym
void h(int dest, std::vector<int> matrix, int verticesAmount, std::vector<int> &heuristicWeight);

//Algorytm przeszukiwania A*
int findPathAStar(int source, int dest, std::vector<int> matrix, int verticesAmount);

//Algorytm przeszukiwania zachłannego - Dijkstra
int findPathGreedy(int source, int dest, std::vector<int> matrix, int verticesAmount);

//Algorytm przeszukiwania brute-force, złożoność czasowa rzędu n!, złożoność pamięciowa rzędu n^2.
int findPathBruteForce(std::vector<int> matrix, int startPoint, int finishPoint, int verticesAmount);

//Funkcja zwracająca listę kombinacji, przez które musi przejść algorytm Brute Force.
std::vector<std::vector<int>> comb(int N, int K);