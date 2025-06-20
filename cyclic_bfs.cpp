#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

const int V = 7; 


char vertexName(int index) {
    return 'A' + index;
}

int adjMatrix[V][V] = {
    {0, 0, 1, 0, 0, 0, 0}, 
    {0, 0, 1, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0},
    {1, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0} 
};

bool bfsDirected(int start, vector<char>& cycle) {
    vector<bool> visited(V, false);
    vector<bool> inQueue(V, false);
    vector<int> parent(V, -1);
    queue<int> q;

    q.push(start);
    visited[start] = true;
    inQueue[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inQueue[u] = false;

        for (int v = 0; v < V; ++v) {
            if (adjMatrix[u][v]) {
                if (!visited[v]) {
                    visited[v] = true;
                    parent[v] = u;
                    q.push(v);
                    inQueue[v] = true;
                } else if (inQueue[v]) {
                    cycle.clear();
                    cycle.push_back(vertexName(v));
                    int curr = u;
                    while (curr != v && curr != -1) {
                        cycle.push_back(vertexName(curr));
                        curr = parent[curr];
                    }
                    cycle.push_back(vertexName(v));
                    reverse(cycle.begin(), cycle.end());
                    return true;
                }
            }
        }
    }

    return false;
}

bool bfsUndirected(int start, vector<char>& cycle) {
    vector<bool> visited(V, false);
    vector<int> parent(V, -1);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; ++v) {
            if (adjMatrix[u][v] || adjMatrix[v][u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    parent[v] = u;
                    q.push(v);
                } else if (v != parent[u]) {
                    // Cycle found
                    cycle.clear();
                    int curr = u;
                    while (curr != -1) {
                        cycle.push_back(vertexName(curr));
                        if (curr == v) break;
                        curr = parent[curr];
                    }
                    cycle.push_back(vertexName(v));
                    reverse(cycle.begin(), cycle.end());
                    return true;
                }
            }
        }
    }

    return false;
}

int main() {
    vector<char> cycle;

    cout << "=== Cycle Detection using BFS (Directed Graph) ===\n";
    if (bfsDirected(3, cycle)) { 
        cout << "Cycle detected: ";
        for (char c : cycle)
            cout << c << " ";
        cout << endl;
    } else {
        cout << "No cycle detected in directed graph.\n";
    }

    cout << "\n=== Cycle Detection using BFS (Undirected Graph) ===\n";
    if (bfsUndirected(3, cycle)) {
        cout << "Cycle detected: ";
        for (char c : cycle)
            cout << c << " ";
        cout << endl;
    } else {
        cout << "No cycle detected in undirected graph.\n";
    }

    return 0;
}
