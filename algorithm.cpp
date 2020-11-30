//
// Created by Jakub Strawa on 11/29/20.
//

#include <chrono>
#include "algorithm.h"


void h(int dest, std::vector<int> matrix, int verticesAmount, std::vector<int> &heuristicWeight){
    int currentVertice = dest;
    int distance = 1;
    std::vector<int> visited;
    std::vector<int> unvisited;
    unvisited.push_back(currentVertice);
    heuristicWeight[dest - 1] = 0;

    while (!unvisited.empty()){
        for (int j = verticesAmount - 1; j >= 0; j--) {
            if (matrix[j * verticesAmount + currentVertice - 1] != INF) {
                if (heuristicWeight[j] > distance) {
                    heuristicWeight[j] = distance;
                }
                if (std::find(unvisited.begin(), unvisited.end(), (j + 1)) == unvisited.end()
                    && std::find(visited.begin(), visited.end(), (j + 1)) == visited.end()) {
                    unvisited.push_back(j + 1);
                }
            }
        }
        visited.push_back(currentVertice);
        unvisited.erase(std::find(unvisited.begin(), unvisited.end(), currentVertice));
        if (!unvisited.empty()){
            currentVertice = unvisited[0];
            distance = heuristicWeight[currentVertice - 1] + 1;
        }
    }

    std::cout << "Heuristic: " << '\n';
    for (auto v : heuristicWeight){
        std::cout <<  v << ", ";
    }
}

int findPathAStar(int source, int dest, std::vector<int> matrix, int verticesAmount){
    std::vector<int> visited;
    std::vector<int> unvisited;
    std::vector<std::tuple<int, int, int>> minimalCost;   // odległość minimalna od początku, odległość + heurystyka h(), path
    std::vector<int> heuristicWeight;
    int currentVertice = source;

    for (int i = 1; i <= verticesAmount; i++){
        if (i == source){
            minimalCost.push_back(std::make_tuple(0, 0, 0));
            unvisited.push_back(i);
        } else {
            minimalCost.push_back(std::make_tuple(INF, INF, 0));
        }
        heuristicWeight.push_back(INF);
    }

    h(dest, matrix, verticesAmount, heuristicWeight);


    while(currentVertice != dest){
        for (int j = 1; j <= verticesAmount; j++) {
            if (matrix[(currentVertice - 1)*verticesAmount + j - 1] != INF){
                if (std::find(unvisited.begin(), unvisited.end(), j) == unvisited.end()
                    && std::find(visited.begin(), visited.end(), j) == visited.end()){
                    unvisited.push_back(j);
                }

                if (std::get<0>(minimalCost[j - 1]) > std::get<0>(minimalCost[currentVertice - 1]) + matrix[(currentVertice - 1)*verticesAmount + j - 1]){
                    std::get<0>(minimalCost[j - 1]) = std::get<0>(minimalCost[currentVertice - 1]) + matrix[(currentVertice - 1)*verticesAmount + j - 1];
                    std::get<2>(minimalCost[j - 1]) = currentVertice;
                    std::get<1>(minimalCost[j - 1]) = std::get<0>(minimalCost[j - 1]) + heuristicWeight[j  - 1];
                }

            }
        }
        visited.push_back(currentVertice);
        unvisited.erase(std::find(unvisited.begin(), unvisited.end(), currentVertice));
        if (!unvisited.empty()){
            currentVertice = unvisited[0];
            for (auto v : unvisited){
                if (std::get<1>(minimalCost[v - 1]) < std::get<1>(minimalCost[currentVertice - 1])){
                    currentVertice = v;
                }
            }
            if (currentVertice == dest){
                break;
            }
        }

    }

    std::cout << "Visited: ";
    for (auto v : visited){
        std::cout << v << " ";
    }
    std::cout << '\n' << "Minimal cost: ";
    for (auto v : minimalCost){
        std::cout << std::get<0>(v) << " ";
    }
    std::cout << '\n' << "Path: ";
    for (auto v : minimalCost){
        std::cout << std::get<2>(v) << " ";
    }
    std::cout << '\n' << "Optimal path: ";
    currentVertice = dest;
    while (currentVertice != source){
        std::cout << currentVertice << " <- ";
        currentVertice = std::get<2>(minimalCost[currentVertice - 1]);
    }
    std:: cout << source;
    std::cout << '\n';

    return std::get<0>(minimalCost[dest - 1]);
}

int findPathGreedy(int source, int dest, std::vector<int> matrix, int verticesAmount){
    std::vector<int> visited;
    std::vector<int> unvisited;
    std::vector<std::pair<int, int>> minimalCost; //minimal cost, path
    int currentVertice = source;

    for (int i = 1; i <= verticesAmount; i++){
        if (i == source){
            minimalCost.push_back(std::make_pair(0, 0));
            unvisited.push_back(i);
        } else {
            minimalCost.push_back(std::make_pair(INF, 0));
            //unvisited.push_back(std::make_pair(i, INF));
        }
    }

    while(visited.size() != verticesAmount){
        for (int j = 1; j <= verticesAmount; j++) {
            if (matrix[(currentVertice - 1)*verticesAmount + j - 1] != INF){
                if (std::find(unvisited.begin(), unvisited.end(), j) == unvisited.end()
                    && std::find(visited.begin(), visited.end(), j) == visited.end()){
                    unvisited.push_back(j);
                }
                if (minimalCost[j - 1].first > minimalCost[currentVertice - 1].first + matrix[(currentVertice - 1)*verticesAmount + j - 1]){
                    minimalCost[j - 1].first = minimalCost[currentVertice - 1].first + matrix[(currentVertice - 1)*verticesAmount + j - 1];
                    minimalCost[j - 1].second = currentVertice;

                }

            }
        }
        visited.push_back(currentVertice);
        unvisited.erase(std::find(unvisited.begin(), unvisited.end(), currentVertice));
        if (!unvisited.empty()){
            currentVertice = unvisited[0];
            for (auto v : unvisited){
                if (minimalCost[v - 1].first < minimalCost[currentVertice - 1].first){
                    currentVertice = v;
                }
            }
            /*
            if (currentVertice == dest){
                break;
            } */
        }

    }

    std::cout << "Visited: ";
    for (auto v : visited){
        std::cout << v << " ";
    }
    std::cout << '\n' << "Minimal cost: ";
    for (auto v : minimalCost){
        std::cout << v.first << " ";
    }
    std::cout << '\n' << "Path: ";
    for (auto v : minimalCost){
        std::cout << v.second << " ";
    }
    std::cout << '\n' << "Optimal path: ";
    currentVertice = dest;
    while (currentVertice != source){
        std::cout << currentVertice << " <- ";
        currentVertice = minimalCost[currentVertice - 1].second;
    }
    std:: cout << source;
    std::cout << '\n';


    return minimalCost[dest-1].first;
}

int findPathBruteForce(std::vector<int> matrix, int startPoint, int finishPoint, int verticesAmount){
    int source = startPoint - 1;
    std::vector<int> nodes;
    std::vector<int> nodes2;
    std::vector<int> path;
    std::vector<std::vector<int>> v2;
    auto start = std::chrono::steady_clock::now();
    auto stop = std::chrono::steady_clock::now();

    int shortest_path = INF;
    for(int i=1 ;i<finishPoint;i++)
    {
        v2 = comb(finishPoint-1, i);

        while(!v2.empty())
        {
            nodes2 = v2[v2.size()-1];
            if(nodes2.back() == -1) return -1;
            //std::cout << "number of lines:" << v2.size()/i;
            for(int m =0;m<v2.size();m++)
            {
                nodes2 = v2[m];
                for(int k=0;k<i;k++)
                {
                    nodes.push_back(nodes2.back());
                    nodes2.pop_back();
                }
                /*std::cout << "number of lines:" << v2.size()/i;
                std::cout << "next combination:";
                for (auto v: nodes) {
                    std::cout << v + 1 << " ";
                }
                std::cout << "\n";*/
                int n = 0;

                int path_weight = 0;
                sort(nodes.begin(),nodes.end());
                //std::cout << "\n";
                do {
                    nodes.push_back(finishPoint - 1);
                    /*for (auto v: nodes) {
                        std::cout << v + 1 << " ";
                    }*/

                    //std::cout << "\n";
                    int j = source;
                    n = nodes.size();
                    for (int i = 0; i < n; i++) {
                        path_weight += matrix[j * verticesAmount + nodes[i]];
                        //std::cout << path_weight << std::endl;
                        j = nodes[i];
                        if (path_weight >= 10000)
                        {
                            //nodes.pop_back();
                            break;
                        }
                    }

                    //std::cout << path_weight << std::endl;
                    shortest_path = std::min(shortest_path, path_weight);
                    if (shortest_path == path_weight) {
                        path = nodes;
                    }
                    //std::cout << "shortest: " << shortest_path << std::endl;
                    nodes.pop_back();
                    path_weight = 0;
                    stop = std::chrono::steady_clock::now();
                    std::chrono::duration<double> elapsed = stop-start;
                    //std::cout << elapsed.count();
                    if(elapsed.count() > 3) return -1;
                } while(std::next_permutation(nodes.begin(), nodes.end()));

                nodes.clear();
            }
            v2.clear();

        }

    }

    std::cout << "Optimal path: " << startPoint;
    for(auto v: path)
    {
        std::cout <<" -> " << v+1;
    }
    std::cout << "\n";
    return shortest_path;
}


std::vector<std::vector<int>> comb(int N, int K)
{
    auto start = std::chrono::steady_clock::now();
    auto stop = std::chrono::steady_clock::now();
    std::string bitmask(K, 1);
    bitmask.resize(N, 0);
    std::vector<int> v2;
    std::vector<std::vector<int>> v1;

    do {
        for (int i = 0; i < N; ++i)
        {
            if (bitmask[i])
            {
                v2.push_back(i);
                //std::cout << " " << i;
            }
        }
        stop = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = stop-start;
        //std::cout << elapsed.count();
        if(elapsed.count() > 3)
        {
            v2.push_back(-1);
            v1.push_back(v2);
            break;
        }
        //std::cout << "\n";
        v1.push_back(v2);
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));

    return v1;
}