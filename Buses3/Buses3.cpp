#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
    Graph graph(5);

    graph.addEdge("B1", "B2", 9);
    graph.addEdge("B1", "B3", 4);
    graph.addEdge("B3", "B4", 3);
    graph.addEdge("B4", "B2", 1);
    graph.addEdge("B4", "B5", 6);
    graph.addEdge("B2", "B5", 5);

    cout << endl << "--------------- our graph -------------------" << endl;

    graph.printMatrix(graph.matrix);

    cout << endl << "------- after using floyd warshall ----------" << endl;



    vector<string> buses;
    buses.push_back("B5");
    buses.push_back("B4");
    buses.push_back("B3");
    buses.push_back("B2");


    graph.add_bus(buses.size(), "B1", buses);
}
