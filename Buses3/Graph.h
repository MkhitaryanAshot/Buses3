#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
#include <queue>

#define INF 9999999
using namespace std;

class Graph {
public:
    int numVertices;
    vector<vector<int>> matrix;
    map<string, int> index;
    vector<pair<int, vector<string>>> buses;
    int busNumber = 0;

    Graph(int numVertices) : numVertices(numVertices) {
        matrix.resize(numVertices, vector<int>(numVertices, INF));
    }

    void newGraph(int newV) {

        matrix.clear();
        numVertices = newV;
        matrix.resize(numVertices, vector<int>(numVertices, INF));
    }

    void resizeMatrix(int newSize) {
        vector<vector<int>> newMatrix(newSize, vector<int>(newSize, INF));
        for (int i = 0; i < min(numVertices, newSize); ++i) {
            for (int j = 0; j < min(numVertices, newSize); ++j) {
                newMatrix[i][j] = matrix[i][j];
            }
        }
        matrix = newMatrix;
        numVertices = newSize;
    }


    void addEdge(string u, string v, int k)
    {
        int uIndex = getIndex(u);
        int vIndex = getIndex(v);
        matrix[uIndex][vIndex] = k;
    }


    int getIndex(const string& x) {
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
                    cout << 0 << " ";
                }
                else {
                    cout << dest[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

    vector<vector<int>> floydWarshall()
    {
        vector<vector<int>> reserved = matrix;

        for (int k = 0; k < numVertices; ++k) {
            for (int i = 0; i < numVertices; ++i) {
                for (int j = 0; j < numVertices; ++j) {
                    if (reserved[i][k] != INF && reserved[k][j] != INF && reserved[i][j] > (reserved[i][k] + reserved[k][j])) {
                        reserved[i][j] = reserved[i][k] + reserved[k][j];
                    }
                }
            }
        }
        return reserved;
    }


    void add_bus(vector<vector<int>> reserved)
    {
        vector<string> streets;
        string a;
        string s;
        int k;

        cout << "Enter the crossroad for bus to start ";
        cin >> a;
        streets.push_back(a);


        cout << "Enter the number of bus stations ";
        cin >> k;

        for (int i = 1; i <= k; i++)
        {
            cout << "Enter " << i << " bus station ";
            cin >> s;
            streets.push_back(s);

        }

        busNumber++;
        buses.push_back(make_pair(busNumber, streets));


        int start = getIndex(a);

        int min = reserved[start][getIndex(streets[0])];

        int count = 0;


        for (int i = 0; i < streets.size(); ++i)
        {
            int minDuration = reserved[start][getIndex(streets[i])];
            if (minDuration < min)
            {
                min = minDuration;
                count = i;
            }
        }

        if (min != INF) {
            cout << "The closest station from " << a << " is " << streets[count] << endl;
            cout << "Duration is " << min << endl;
        }
        else {
            cout << "There is no path from " << a << " to any station ";
        }
    }


    void Construct_crossroad()
    {
        resizeMatrix(numVertices + 1);

        int k;
        int m;
        string a;
        vector<string> crossroads;

        cout << "Enter the name of new crossroad ";
        cin >> a;
        cout << "Enter the count of streets to leading in " << a << " crossroad ";
        cin >> k;

        while (k != 0)
        {
            string street;
            cout << "Enter the street ";
            cin >> street;
            crossroads.push_back(street);

            int duration;
            cout << "Enter the duration from " << street << " to " << a << " ";
            cin >> duration;

            addEdge(street, a, duration);
            k--;
        }

        cout << "Enter the count of outgoing streets from " << a << " crossroad ";
        cin >> m;
        while (m != 0)
        {
            string street;
            cout << "Enter the street ";
            cin >> street;
            crossroads.push_back(street);

            int duration;
            cout << "Enter the duration from " << street << " to " << a << " ";
            cin >> duration;

            addEdge(a, street, duration);
            m--;
        }

        vector<vector<int>> reserved = floydWarshall();


        if (buses.size() == 0) {
            cout << "There is no bus path to update " << endl;
        }
        for (int i = 0; i < buses.size(); ++i)
        {

            int start = getIndex(buses[i].second[0]);
            for (int j = 1; j < buses[i].second.size(); j++)
            {
                int minDuration = reserved[start][getIndex(buses[i].second[j])];
                cout << "The shortest duration from " << buses[i].second[0] << " crossroad to " << buses[i].second[j] << " is " << minDuration << " min" << endl;
            }
        }
    }

    vector<int> dijkstra(int source) {
        vector<int> dist(numVertices, INF);
        dist[source] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({ 0, source });

        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            if (d > dist[u]) continue;

            for (int v = 0; v < numVertices; ++v) {
                if (matrix[u][v] != INF) {
                    int new_dist = dist[u] + matrix[u][v];
                    if (new_dist < dist[v]) {
                        dist[v] = new_dist;
                        pq.push({ new_dist, v });
                    }
                }
            }
        }

        return dist;
    }


    void Common_Streets()
    {
        int i;
        int j;
        cout << "Enter the first bus number (0,1,2...)" << endl;
        cin >> i;
        cout << "Enter the second bus number to compare" << endl;
        cin >> j;

        if (buses.empty()) {
            cout << "No bus available." << endl;
            return;
        }

        if (i < 0 || i >= buses.size() || j < 0 || j >= buses.size()) {
            cout << "There is no bus with this number" << endl;
            return;
        }

        vector<string> first = buses[i].second;
        vector<string> second = buses[j].second;

        vector<int> dist_first = dijkstra(getIndex(first[0]));
        bool commonStreetsFound = false;

        cout << "Common streets between bus " << i << " and bus " << j << ":" << endl;
        for (const string& street : first) {
            int idx = getIndex(street);
            if (dist_first[idx] != INF) {

                if (find(second.begin(), second.end(), street) != second.end() && dist_first[idx] < INF) {
                    cout << street << endl;
                    commonStreetsFound = true;
                }
            }
        }
        if (!commonStreetsFound) {
            cout << "There are no common streets between bus " << i << " and bus " << j << "." << endl;
        }
    }
};