#include <iostream>
#include <vector>
#include <map>
#include <climits>
#include <queue>
#include <stack>
using namespace std;

const int MAX = 100;

int graph[MAX][MAX]; // Adjacency matrix
map<string, int> cityIndex;
vector<string> cityNames;
int cityCount = 0;

void addCity(string name) {
    if (cityIndex.find(name) == cityIndex.end()) {
        cityIndex[name] = cityCount++;
        cityNames.push_back(name);
        cout << "City added: " << name << endl;
    } else {
        cout << "City already exists!" << endl;
    }
}

void addRoute(string src, string dest, int dist) {
    if (cityIndex.find(src) == cityIndex.end() || cityIndex.find(dest) == cityIndex.end()) {
        cout << "Both cities must be added first.\n";
        return;
    }

    int u = cityIndex[src];
    int v = cityIndex[dest];
    graph[u][v] = dist;
    graph[v][u] = dist; // Assuming bidirectional roads
    cout << "Route added: " << src << " <--> " << dest << " [" << dist << " km]\n";
}

void dijkstra(string startCity, string endCity) {
    if (cityIndex.find(startCity) == cityIndex.end() || cityIndex.find(endCity) == cityIndex.end()) {
        cout << "One or both cities do not exist.\n";
        return;
    }

    int start = cityIndex[startCity];
    int end = cityIndex[endCity];

    vector<int> dist(cityCount, INT_MAX);
    vector<int> parent(cityCount, -1);
    vector<bool> visited(cityCount, false);

    dist[start] = 0;
    for (int i = 0; i < cityCount - 1; ++i) {
        int u = -1;
        int minDist = INT_MAX;

        for (int j = 0; j < cityCount; ++j) {
            if (!visited[j] && dist[j] < minDist) {
                u = j;
                minDist = dist[j];
            }
        }

        if (u == -1) break;
        visited[u] = true;

        for (int v = 0; v < cityCount; ++v) {
            if (graph[u][v] && !visited[v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    if (dist[end] == INT_MAX) {
        cout << "No route found from " << startCity << " to " << endCity << ".\n";
        return;
    }

    // Display route
    stack<int> path;
    for (int v = end; v != -1; v = parent[v]) {
        path.push(v);
    }

    cout << "Shortest path from " << startCity << " to " << endCity << ": ";
    while (!path.empty()) {
        cout << cityNames[path.top()];
        path.pop();
        if (!path.empty()) cout << " -> ";
    }

    cout << "\nTotal distance: " << dist[end] << " km\n";
}

int main() {
    int choice;

    while (true) {
        cout << "\n--- Optimal Route Planning Menu ---\n";
        cout << "1. Add City\n2. Add Route\n3. Find Optimal Route\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            cout << "Enter city name: ";
            cin >> name;
            addCity(name);
        }
        else if (choice == 2) {
            string src, dest;
            int dist;
            cout << "Enter source city: ";
            cin >> src;
            cout << "Enter destination city: ";
            cin >> dest;
            cout << "Enter distance (km): ";
            cin >> dist;
            addRoute(src, dest, dist);
        }
        else if (choice == 3) {
            string start, end;
            cout << "Enter starting city: ";
            cin >> start;
            cout << "Enter destination city: ";
            cin >> end;
            dijkstra(start, end);
        }
        else if (choice == 4) {
            cout << "Exiting...\n";
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
