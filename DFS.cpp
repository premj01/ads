#include <iostream>
#include <stack>
#include <vector>
using namespace std;

void DFS(vector<vector<int>> &graph, vector<bool> &visited, int startnode, int nodes)
{
    stack<int> s;

    s.push(startnode);
    visited[startnode] = true;

    cout << "Graph DFS traversal Order is ";

    while (!s.empty())
    {
        int node = s.top();
        s.pop();

        cout << node << endl;

        for (int i = 0; i < nodes; i++)
        {
            if (graph[node][i] == 1 && !visited[i])
            {
                s.push(i);
                visited[i] = true;
            }
        }
    }
}

int main()
{
    int nodes;
    cout << "Enter number of nodes :";
    cin >> nodes;

    // int graph[nodes][nodes] = {0};
    vector<vector<int>> graph(nodes, vector<int>(nodes, 0));
    vector<bool> visited(nodes, false);

    int edgs;
    cout << "Now enter number of edges :";
    cin >> edgs;

    for (int i = 0; i < edgs; i++)
    {
        int u, v;
        cout << "Enter (U,V) :";
        cin >> u >> v;
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    DFS(graph, visited, 0, nodes);

    return 0;
}