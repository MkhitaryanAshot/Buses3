#include <iostream>
#include "Graph.h"

using namespace std;

void testcase1(Graph& graph) {
    graph.newGraph(11);


    graph.addEdge("B1", "B9", 5);
    graph.addEdge("B2", "B3", 2);
    graph.addEdge("B3", "B4", 3);
    graph.addEdge("B3", "B4", 3);
    graph.addEdge("B3", "B6", 4);
    graph.addEdge("B6", "B5", 2);
    graph.addEdge("B5", "B1", 3);
    graph.addEdge("B4", "B7", 8);
    graph.addEdge("B6", "B8", 3);
    graph.addEdge("B7", "B8", 4);
    graph.addEdge("B9", "B8", 6);
    graph.addEdge("B10", "B9", 7);
    graph.addEdge("B8", "B11", 6);
    graph.addEdge("B11", "B10", 5);
};


void testcase2(Graph& graph) {
    graph.newGraph(6);

    graph.addEdge("B1", "B2", 4);
    graph.addEdge("B2", "B3", 9);
    graph.addEdge("B1", "B4", 2);
    graph.addEdge("B4", "B5", 6);
    graph.addEdge("B3", "B6", 5);
    graph.addEdge("B6", "B5", 3);
    graph.addEdge("B5", "B1", 1);
    graph.addEdge("B5", "B3", 4);


}

void testcase3(Graph& graph) {
    graph.newGraph(8);


    graph.addEdge("B1", "B2", 2);
    graph.addEdge("B1", "B3", 1);
    graph.addEdge("B2", "B3", 3);
    graph.addEdge("B2", "B4", 4);
    graph.addEdge("B3", "B4", 1);
    graph.addEdge("B3", "B5", 7);
    graph.addEdge("B4", "B6", 5);
    graph.addEdge("B5", "B6", 2);
    graph.addEdge("B6", "B7", 3);
    graph.addEdge("B7", "B8", 4);
    graph.addEdge("B8", "B5", 2);

}

int main() {
    cout << "Choose the options" << endl;
    cout << "1. Test case 1" << endl;
    cout << "2. Test case 2" << endl;
    cout << "3. Test case 3" << endl;
    cout << "4. Manual input" << endl;

    int x;
    cin >> x;

    Graph graph(0);

    if (x == 1) {
        testcase1(graph);
    }
    else if (x == 2) {
        testcase2(graph);
    }
    else if (x == 3) {
        testcase3(graph);
    }
    else if (x == 4) {
        int n;
        int m;

        cout << "Enter the number of crossroads ";
        cin >> n;

        cout << "Enter the number of streets ";
        cin >> m;

        graph.newGraph(n);

        while (m != 0) {
            string u;
            string v;
            int k;

            cout << "Enter first street ";
            cin >> u;

            cout << "Enter second street ";
            cin >> v;

            cout << "Enter the duration in minutes required to drive through the street ";
            cin >> k;

            graph.addEdge(u, v, k);

            m--;
        }
        cout << "------------Your graph------------" << endl;
        graph.printMatrix(graph.matrix);


    }
    else {
        cout << "Invalid option" << endl;
        return 0;
    }

    vector<vector<int>> reserved = graph.floydWarshall();
    cout << endl;

    while (true) {
        cout << "Choose the exercise to start" << endl;
        cout << "1. Add Bus" << endl;
        cout << "2. Construct Crossroad" << endl;
        cout << "3. Common Streets" << endl;
        cout << "4. Exit" << endl;
        int k;
        cin >> k;

        if (k == 1) {
            graph.add_bus(reserved);
        }
        else if (k == 2) {
            graph.Construct_crossroad();
        }
        else if (k == 3) {
            graph.Common_Streets();
        }
        else if (k == 4) {
            break;
        }
        else {
            cout << "Invalid option" << endl;
        }
        cout << endl;
    }


    return 0;
}
