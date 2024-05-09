#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
    map<string, vector<string>> adj;

    void addEdge(string person1, string person2)
    {
        adj[person1].push_back(person2);
        adj[person2].push_back(person1);
    }

    void printGraph()
    {
        for (auto person : adj)
        {
            cout << person.first << " -> ";
            for (auto neighbour : person.second)
            {
                cout << neighbour << " ";
            }
            cout << endl;
        }
    }

    void BFS_Traversal(string src)
    {
        vector<string> result;
        set<string> visited;
        queue<string> q;

        visited.insert(src);
        q.push(src);

        while (!q.empty())
        {
            string person = q.front();
            q.pop();

            result.push_back(person);

            for (auto neighbour : adj[person])
            {
                if (visited.find(neighbour) == visited.end())
                {
                    visited.insert(person);
                    q.push(neighbour);
                }
            }
        }

        printResult("BFS", result);
    }

    void DFS(string person, set<string> &visited, vector<string> &result)
    {
        result.push_back(person);
        visited.insert(person);

        for (auto neighbour : adj[person])
        {
            if (visited.find(neighbour) == visited.end())
            {
                DFS(neighbour, visited, result);
            }
        }
    }

    void DFS_Traversal(string person)
    {
        vector<string> result;
        set<string> visited;

        DFS(person, visited, result);

        printResult("DFS", result);
    }

    void printResult(string name, vector<string> &traversal)
    {
        cout << name << " Traversal -> ";
        for (auto person : traversal)
        {
            cout << person << " ";
        }
        cout << endl;
    }
};

int main()
{
    Graph g;
    g.addEdge("person1", "person2");
    g.addEdge("person1", "person3");
    g.addEdge("person2", "person4");
    g.addEdge("person3", "person5");
    g.addEdge("person4", "person6");

    g.printGraph();

    g.BFS_Traversal("person1");
    g.DFS_Traversal("person1");

    return 0;
}