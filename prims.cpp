#include <iostream>
#include <climits>
#include <vector>
#include <queue>
using namespace std;

class Graph
{
public:
    int MaxCities = 100;
    int cityCount = 0;
    int adjMatrix[100][100];
    string cities[100];

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
            cout << "Both cities should be present";
        }

        adjMatrix[index1][index2] = distance;
        adjMatrix[index2][index1] = distance;
    }

    void prims(string city)
    {
        int start = getCityIndex(city);
        if (start == -1)
        {
            cout << "invalid city";
        }

        vector<int> key(cityCount, INT_MAX);
        vector<bool> inMST(cityCount, false);
        vector<int> parent(cityCount, -1);

        key[start] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        pq.push({0, start});

        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

            if (inMST[u])
                continue;
            inMST[u] = true;

            for (int v = 0; v < cityCount; v++)
            {
                if (adjMatrix[u][v] != INT_MAX && !inMST[v] && adjMatrix[u][v] < key[v])
                {
                    key[v] = adjMatrix[u][v];
                    pq.push({key[v], v});
                    parent[v] = u;
                }
            }
        }

        cout << "Minimum spaninning tree" << endl;
        for (int i = 0; i < cityCount; i++)
        {
            if (parent[i] != -1)
            {
                cout << cities[parent[i]] << "\t --- \t" << cities[i] << "\tdistance\t" << adjMatrix[parent[i]][i] << endl;
            }
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
    // Graph *g = new Graph();
    // g->addCityToGraph("Nashik");
    // g->addCityToGraph("Pune");
    // g->addCityToGraph("Nagar");
    // g->addCityToGraph("Dhule");

    // g->addRoute("Nashik", "Pune", 200);
    // g->addRoute("Nashik", "Nagar", 300);
    // g->addRoute("Nagar", "Pune", 100);
    // g->addRoute("Dhule", "Nashik", 150);

    // g->display();

    // g->prims("Nashik");
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
        cout << "4. Run Prim's Algorithm (MST)" << endl;
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
            cout << "Enter the starting city for Prim's algorithm: ";
            cin >> city1;
            g.prims(city1);
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
