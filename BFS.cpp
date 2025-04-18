#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void BFS(vector<vector<int>> graph, vector<bool> visited, int startnode, int nodes)
{
    queue<int> q;

    q.push(startnode);
    visited[startnode] = true;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        cout << node << endl;

        for (int i = 0; i < nodes; i++)
        {
            if (graph[node][i] == 1 && !visited[i])
            {
                q.push(i);
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

    vector<vector<int>> graph(nodes, vector<int>(nodes, 0));
    vector<bool> visited(nodes, false);

    int edges;
    cout << "Enter number of edges :";
    cin >> edges;

    cout << "Now enter edges one by one (U V) : ";
    for (int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    BFS(graph, visited, 0, nodes);

    return 0;
}