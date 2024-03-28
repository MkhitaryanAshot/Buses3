#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>

#define INF 9999999
using namespace std;

class Graph {
public:
    int numVertices;
    vector<vector<int>> matrix;
    unordered_map<string, int> index;

    Graph(int numVertices) : numVertices(numVertices) {
        matrix.resize(numVertices, vector<int>(numVertices, 0));
    }

    void addEdge(string u, string v, int k) {
        int uIndex = getIndex(u);
        int vIndex = getIndex(v);
        matrix[uIndex][vIndex] = k;
        matrix[vIndex][uIndex] = k;
    }

    int getIndex(string& x) {
        if (index.find(x) != index.end()) {
            return index[x];
        }
        else {
            int newIndex = index.size();
            index[x] = newIndex;
            return newIndex;
        }
    }

    void printMatrix(vector<vector<int>> dest) {
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (dest[i][j] == INF) {
                    cout << " - " << " ";
                }
                else {
                    cout << dest[i][j] << "   ";
                }
            }
            cout << endl;
        }
    }

    vector<vector<int>> floydWarshall() {
        vector<vector<int>> reserved = matrix;
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (reserved[i][j] == 0) {
                    reserved[i][j] = INF;
                }
            }
        }
        int n = reserved.size();
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (reserved[i][j] > (reserved[i][k] + reserved[k][j]) && (reserved[k][j] != INF && reserved[i][k] != INF)) reserved[i][j] = reserved[i][k] + reserved[k][j];
                }
            }
        }
        return reserved;
    }

    void add_bus(int k, string A, vector<string> buses) {
        vector<vector<int>> reserved = floydWarshall();
        int start = getIndex(A);
        int min = reserved[getIndex(buses[0])][start];
        int count = 0;
        for (int i = 1; i < buses.size(); ++i) {
            if (reserved[getIndex(buses[i])][start] < min) {
                min = reserved[getIndex(buses[i])][start];
                count = i;
            }
        }

        cout << "The shortest crossroad from " << A << " is " << buses[count] << endl;
        cout << "Time duration is " << min << endl;
    }
};