#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int V = 7; 
const string labels = "ABCDEFG";

bool dfsCycle(int u, vector<vector<int>>& adjMatrix, vector<int>& color, vector<int>& parent, vector<int>& cyclePath) {
    color[u] = 1; 

    for (int v = 0; v < V; ++v) {
        if (adjMatrix[u][v]) {
            if (color[v] == 0) { 
                parent[v] = u;
                if (dfsCycle(v, adjMatrix, color, parent, cyclePath))
                    return true;
            } else if (color[v] == 1) { 
                cyclePath.clear();
                int temp = u;
                cyclePath.push_back(v);
                while (temp != v) {
                    cyclePath.push_back(temp);
                    temp = parent[temp];
                }
                cyclePath.push_back(v);
                reverse(cyclePath.begin(), cyclePath.end());
                return true;
            }
        }
    }

    color[u] = 2; 
    return false;
}

bool detectCycleDFS(vector<vector<int>>& adjMatrix, vector<int>& cyclePath) {
    vector<int> color(V, 0); 
    vector<int> parent(V, -1);

    vector<int> order = {3, 0, 1, 2, 4, 5, 6};

    for (int u : order) {
        if (color[u] == 0) {
            if (dfsCycle(u, adjMatrix, color, parent, cyclePath))
                return true;
        }
    }

    return false;
}

int main() {
    vector<vector<int>> adjMatrix = {
        {0, 0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 1, 1, 1}, 
        {1, 0, 0, 0, 1, 0, 0}, 
        {1, 0, 0, 0, 0, 0, 0}, 
        {0, 1, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0}  
    };

    vector<int> cyclePath;
    if (detectCycleDFS(adjMatrix, cyclePath)) {
        cout << "Cycle detected: ";
        for (int node : cyclePath)
            cout << labels[node] << " ";
        cout << endl;
    } else {
        cout << "No cycle detected.\n";
    }

    return 0;
}
