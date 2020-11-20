#include <iostream>
#include "graph.cpp"

//Algorytm przeszukiwania A*
int findPathAStar(std::vector<std::tuple<int, int, int>> graph){
    int cost = 0;

    return cost;
}

//Algorytm przeszukiwania zachłannego - Dijkstra
int findPathGreedy(std::vector<std::tuple<int, int, int>> graph){
    int cost = 0;

    return cost;
}

//Algorytm przeszukiwania brute-force, złożoność czasowa rzędu n!, złożoność pamięciowa rzędu n^2.
int findPathBruteForce(std::vector<int> matrice, int startPoint, int finishPoint, int verticesAmount){
        int source = startPoint - 1;
        std::vector<int> nodes;

        for(int i=0;i<finishPoint;i++)
        {
            if(i != source)
            {
                nodes.push_back(i);
            }
        }
        int n = nodes.size();
        int shortest_path = 100000;

        while(next_permutation(nodes.begin(),nodes.end()))
        {
            /*for(auto v: nodes)
            {
                std::cout << v+1 << " ";
            }*/
            //std::cout << std::endl;
            int path_weight = 0;

            int j = source;
            for (int i = 0; i < n; i++)
            {
                path_weight += matrice[j*verticesAmount+nodes[i]];
                //std::cout << path_weight << std::endl;
                j = nodes[i];
            }

            //std::cout << path_weight << std::endl;
            shortest_path = std::min(shortest_path, path_weight);
            //std::cout << shortest_path << std::endl;
        }
        return shortest_path;
}

//Sprawdza czy założenia odnośnie wierzchołków są spełnione (kolejne liczby naturalne)
//Jeśli nie, usuwa źle wprowadzone dane
void checkForBadData(){

}

int main(int argc, const char * argv[]) {

    std::vector<std::tuple<int, int, int>> graph;
    int startPoint = 0, finishPoint = 0;

    std::ifstream myfile ("../graph.txt");
    std::string line;
    std::vector<int> vec = {-1,-1,-1};

    //wczytywanie grafu i punktów A oraz B
    if (myfile.is_open()) {

        std::cout << "File opened!" << '\n';
        int spacePos1 = 0, spacePos2 = 0;
        while (getline(myfile, line)) {
            if (line.length() == 5) {
                vec[0] = line[0] - '0';
                vec[1] = line[2] - '0';
                vec[2] = line[4] - '0';

                graph.push_back(std::make_tuple(vec[0], vec[1], vec[2]));
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
                graph.push_back(std::make_tuple(vec[0], vec[1], vec[2]));
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

    //sortowanie wierzchołków
    std::sort(graph.begin(), graph.end(), [](std::tuple<int,int,int> a, std::tuple<int,int,int> b) -> bool
    {
        if (std::get<0>(a) == std::get<0>(b)) {
            return std::get<1>(a) < std::get<1>(b);
        } else {
            return std::get<0>(a) < std::get<0>(b);
        }
    });
    //wyświetlanie grafu
    for (auto v : graph){
        std::cout << std::get<0>(v) << " " << std::get<1>(v) << " " << std::get<2>(v) << '\n';
    }



    //wypisywanie wszystkich wierzchołków
    std::vector<int> vertices;
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

    //sortowanie wektora wierzchołków
    std::sort(vertices.begin(), vertices.end(), [](int a, int b) -> bool
    {
        return a < b;
    });

    std::cout << "Vertices: ";

    for (auto v : vertices){
        std::cout << v << " ";
    }
    std::cout <<  '\n';

    //utworzenie macierzy sąsiedztwa
    int verticesAmount = vertices.size();
    std::vector<int> matrice;
    for (int x = 0; x < verticesAmount*verticesAmount; x++){
        matrice.push_back(100001);
    }

    for (auto &v : graph){
        matrice[(std::get<0>(v)-1)*verticesAmount + (std::get<1>(v)-1)] = std::get<2>(v);
    }

    //wypisanie macierzy sąsiedztwa
    for (int i = 0; i < verticesAmount; i++) {
        for (int j = 0; j < verticesAmount; j++) {
            std::cout.width(10);
            std::cout << matrice[i*verticesAmount + j] << "\t";
        }
        std::cout << '\n';
    }


    std::cout << findPathBruteForce(matrice, startPoint, finishPoint, verticesAmount) << std::endl;

    return 0;
}

