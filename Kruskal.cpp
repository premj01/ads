#include <iostream>
#include <climits>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Graph
{
public:
    int MaxCities = 100;
    int cityCount = 0;
    int adjMatrix[100][100];
    string cities[100];
    vector<pair<int, pair<int, int>>> edges; // {weight, {city1, city2}}

    Graph()
    {
        for (int i = 0; i < MaxCities; i++)
        {
            for (int j = 0; j < MaxCities; j++)
            {
                adjMatrix[i][j] = INT_MAX;
            }
        }
    }

    int getCityIndex(string city)
    {
        for (int i = 0; i < cityCount; i++)
        {
            if (cities[i] == city)
            {
                return i;
            }
        }
        return -1;
    }

    void addCityToGraph(string city)
    {
        if (getCityIndex(city) != -1)
        {
            cout << "City already exists" << endl;
        }
        cities[cityCount++] = city;
        cout << "City added successfully" << endl;
    }

    void addRoute(string city1, string city2, int distance)
    {
        int index1 = getCityIndex(city1);
        int index2 = getCityIndex(city2);

        if (index1 == -1 || index2 == -1)
        {
            cout << "Both cities should be present" << endl;
        }

        adjMatrix[index1][index2] = distance;
        adjMatrix[index2][index1] = distance;

        // Store the edge for Kruskal's
        edges.push_back({distance, {index1, index2}});
    }

    // Union-Find (Disjoint Set) Data Structure for Kruskal's Algorithm
    int find(int parent[], int i)
    {
        if (parent[i] == -1)
            return i;
        return find(parent, parent[i]);
    }

    void unionSet(int parent[], int x, int y)
    {
        parent[x] = y;
    }

    void kruskals()
    {
        // Sort all the edges in ascending order by weight
        sort(edges.begin(), edges.end());

        int parent[cityCount];
        for (int i = 0; i < cityCount; i++)
        {
            parent[i] = -1;
        }

        cout << "Kruskal's Minimum Spanning Tree:" << endl;

        vector<pair<string, pair<string, int>>> mst;

        for (auto edge : edges)
        {
            int u = edge.second.first;
            int v = edge.second.second;
            int weight = edge.first;

            int set_u = find(parent, u);
            int set_v = find(parent, v);

            if (set_u != set_v)
            {
                mst.push_back({cities[u], {cities[v], weight}});
                unionSet(parent, set_u, set_v);
            }
        }

        // Display the MST edges
        for (auto edge : mst)
        {
            cout << edge.first << " --- " << edge.second.first << " \tDistance: " << edge.second.second << endl;
        }
    }

    void display()
    {
        cout << "Graph representation :" << endl;
        for (int i = 0; i < cityCount; i++)
        {
            for (int j = i + 1; j < cityCount; j++)
            {
                if (adjMatrix[i][j] != INT_MAX)
                {
                    cout << cities[i] << "\t---\t" << cities[j] << "\tDistance: " << adjMatrix[i][j] << endl;
                }
            }
        }
    }
};

int main()
{
    Graph g;
    int choice;
    string city1, city2;
    int distance;

    while (true)
    {
        cout << "\nMenu:" << endl;
        cout << "1. Add City" << endl;
        cout << "2. Add Route" << endl;
        cout << "3. Display Graph" << endl;
        cout << "4. Run Kruskal's Algorithm (MST)" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter city name: ";
            cin >> city1;
            g.addCityToGraph(city1);
            break;

        case 2:
            cout << "Enter first city: ";
            cin >> city1;
            cout << "Enter second city: ";
            cin >> city2;
            cout << "Enter distance: ";
            cin >> distance;
            g.addRoute(city1, city2, distance);
            break;

        case 3:
            g.display();
            break;

        case 4:
            g.kruskals();
            break;

        case 5:
            cout << "Exiting..." << endl;
            return 0;

        default:
            cout << "Invalid choice, please try again." << endl;
        }
    }

    return 0;
}
