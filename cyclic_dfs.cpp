#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void printCycle(const vector<int>& parent, int start, int end) {
    vector<int> cycle;
    int current = end;

    while (current != start) {
        cycle.push_back(current);
        current = parent[current];
    }
    cycle.push_back(start);
    cycle.push_back(end);

    cout << "Cycle found: ";
    for (auto it = cycle.rbegin(); it != cycle.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

bool dfsCycle(int node, int parentNode, const vector<vector<int>>& adjMatrix,
              vector<bool>& visited, vector<int>& parentTrack) {
    visited[node] = true;

    for (int v = 0; v < adjMatrix.size(); ++v) {
        if (adjMatrix[node][v]) {
            if (!visited[v]) {
                parentTrack[v] = node;
                if (dfsCycle(v, node, adjMatrix, visited, parentTrack)) {
                    return true;
                }
            } else if (v != parentNode) {
                parentTrack[v] = node;
                printCycle(parentTrack, v, node);
                return true;
            }
        }
    }
    return false;
}

bool isCyclicDFS(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            if (dfsCycle(i, -1, adjMatrix, visited, parent)) {
                return true;
            }
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

    cout << "=== DFS Cycle Detection ===" << endl;
    if (!isCyclicDFS(adjMatrix)) {
        cout << "No cycle found using DFS." << endl;
    }

    return 0;
}