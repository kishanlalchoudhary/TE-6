#include <bits/stdc++.h>
using namespace std;

class Graph
{
    vector<vector<pair<int, int>>> adj;
    int v;

public:
    Graph(int &vertices, vector<vector<int>> &edges)
    {
        v = vertices;

        adj.resize(vertices);
        for (auto edge : edges)
        {
            adj[edge[0]].push_back({edge[1], edge[2]});
            adj[edge[1]].push_back({edge[0], edge[2]});
        }
    }

    vector<int> getPath(int &src, int &dst, vector<int> &parent)
    {
        vector<int> path;
        path.push_back(dst);

        int curr = dst;
        while (curr != src)
        {
            curr = parent[curr];
            path.push_back(curr);
        }

        reverse(path.begin(), path.end());
        return path;
    }

    vector<int> AStar(int &src, int &dst, vector<int> &heuristic)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> open_list;
        vector<bool> close_list(v, false);
        vector<int> parent(v, -1);
        vector<int> f_score(v, INT_MAX);
        vector<int> g_score(v, INT_MAX);

        parent[src] = src;
        close_list[src] = true;
        g_score[src] = 0;
        f_score[src] = heuristic[src];
        open_list.push({f_score[src], src});

        while (!open_list.empty())
        {
            int current = open_list.top().second;
            open_list.pop();

            if (current == dst)
            {
                return getPath(src, dst, parent);
            }

            close_list[current] = true;

            for (auto node : adj[current])
            {
                if (close_list[node.first])
                {
                    continue;
                }

                if (g_score[current] + node.second < g_score[node.first])
                {
                    parent[node.first] = current;
                    g_score[node.first] = g_score[current] + node.second;
                    f_score[node.first] = g_score[node.first] + heuristic[node.first];
                    open_list.push({f_score[node.first], node.first});
                }
            }
        }

        return {};
    }
};

int main()
{
    int vertices = 6;
    int source = 0;
    int destination = 5;
    vector<vector<int>> edges = {
        {0, 1, 2},
        {0, 2, 5},
        {1, 3, 6},
        {1, 4, 3},
        {2, 4, 1},
        {3, 5, 2},
        {4, 5, 5}};
    // Manhattan distance
    vector<int> heuristic = {
        5,
        4,
        3,
        2,
        1,
        0};

    Graph g(vertices, edges);
    vector<int> path = g.AStar(source, destination, heuristic);

    if (path.size() == 0)
    {
        cout << "Path not found from " << source << " to " << destination << endl;
    }
    else
    {
        cout << "Path found from " << source << " to " << destination << ": ";
        for (auto node : path)
        {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}