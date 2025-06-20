#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int V = 7;

char vertexName(int i) {
    return 'A' + i;
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

bool dfsDirected(int u, vector<bool>& visited, vector<bool>& inStack, vector<int>& parent, vector<char>& cycle) {
    visited[u] = true;
    inStack[u] = true;

    for (int v = 0; v < V; ++v) {
        if (adjMatrix[u][v]) {
            if (!visited[v]) {
                parent[v] = u;
                if (dfsDirected(v, visited, inStack, parent, cycle))
                    return true;
            } else if (inStack[v]) {
                cycle.clear();
                int curr = u;
                cycle.push_back(vertexName(v));
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

    inStack[u] = false;
    return false;
}

bool dfsUndirected(int u, int parentU, vector<bool>& visited, vector<int>& parent, vector<char>& cycle) {
    visited[u] = true;

    for (int v = 0; v < V; ++v) {
        if (adjMatrix[u][v] || adjMatrix[v][u]) { 
            if (!visited[v]) {
                parent[v] = u;
                if (dfsUndirected(v, u, visited, parent, cycle))
                    return true;
            } else if (v != parentU) {
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
    return false;
}

int main() {
    vector<char> cycle;

    vector<bool> visitedDir(V, false), inStack(V, false);
    vector<int> parentDir(V, -1);

    cout << "=== DFS Cycle Detection (Directed Graph) ===\n";
    if (dfsDirected(3, visitedDir, inStack, parentDir, cycle)) {
        cout << "Cycle detected: ";
        for (char c : cycle) cout << c << " ";
        cout << endl;
    } else {
        cout << "No cycle detected in directed graph.\n";
    }

    vector<bool> visitedUndir(V, false);
    vector<int> parentUndir(V, -1);

    cout << "\n=== DFS Cycle Detection (Undirected Graph) ===\n";
    if (dfsUndirected(3, -1, visitedUndir, parentUndir, cycle)) {
        cout << "Cycle detected: ";
        for (char c : cycle) cout << c << " ";
        cout << endl;
    } else {
        cout << "No cycle detected in undirected graph.\n";
    }

    return 0;
}
