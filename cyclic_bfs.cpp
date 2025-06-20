#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool bfsCycle(int start, vector<vector<int>>& adjMatrix, vector<bool>& visited, vector<int>& cyclePath) {
    int V = adjMatrix.size();
    vector<int> parent(V, -1);
    queue<int> q;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        for (int neighbor = 0; neighbor < V; ++neighbor) {
            if (adjMatrix[curr][neighbor]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = curr;
                    q.push(neighbor);
                } else if (parent[curr] != neighbor) {
                    cyclePath.clear();
                    int x = curr, y = neighbor;
                    cyclePath.push_back(y);
                    while (x != -1 && x != y) {
                        cyclePath.push_back(x);
                        x = parent[x];
                    }
                    cyclePath.push_back(y);
                    return true;
                }
            }
        }
    }

    return false;
}

bool isCyclic(vector<vector<int>>& adjMatrix, vector<int>& cyclePath) {
    int V = adjMatrix.size();
    vector<bool> visited(V, false);

    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            if (bfsCycle(i, adjMatrix, visited, cyclePath))
                return true;
        }
    }

    return false;
}

int main() {
    vector<vector<int>> adjMatrix = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 1},
        {1, 0, 0, 1, 0}
    };

    vector<int> cyclePath;
    if (isCyclic(adjMatrix, cyclePath)) {
        cout << "Graph contains a cycle.\n";
        cout << "Cycle path: ";
        for (int v : cyclePath)
            cout << v << " ";
        cout << endl;
    } else {
        cout << "Graph does not contain any cycle.\n";
    }

    return 0;
}
