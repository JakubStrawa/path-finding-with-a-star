//
// Created by Jakub Strawa on 11/19/20.
//

#include "graph.h"
#include <vector>
#include <tuple>
#include <fstream>
#include <algorithm>

class Graph {
public:
    Graph(/*std::string path, std::vector<std::tuple<int, in**t, int>> graph*/){
        //readGraph(path, graph);
        readGraph();
    }

    static void readGraph(/*std::string path, std::vector<std::tuple<int, int, int>> graph*/){
        std::ofstream myfile;
        myfile.open ("graph.txt");
        myfile << "Writing this to a file.\n";
        myfile.close();
    }

    void printGraph(){

    }
};
