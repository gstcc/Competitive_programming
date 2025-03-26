#include <vector>
#include <iostream>
#include <climits>
#include <unordered_map>
#include <queue>
#include <algorithm>

const int INF = INT_MAX / 2;

using namespace std;

namespace helper_funcs {

    bool find_augmenting_path(int source, int sink, int n, vector<int>& parent, 
                              const vector<vector<int>>& capacity, const vector<vector<int>>& flow, 
                              unordered_map<int, vector<int>>& adjacent) {
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(source);
        visited[source] = true;
        parent[source] = -1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adjacent[u]) {
                if (!visited[v] && capacity[u][v] > flow[u][v]) {  // If residual capacity > 0
                    parent[v] = u;
                    visited[v] = true;
                    q.push(v);
                    if (v == sink) return true;
                }
            }
        }
        return false;
    }
};

namespace tree_solver {

    // Edmonds-Karp Algorithm: Returns (max_flow, residual flow matrix)
    pair<int, vector<vector<int>>> edmonds_karp(int n, int source, int sink, 
                                                vector<vector<int>>& capacity, 
                                                unordered_map<int, vector<int>>& adjacent) {
        vector<vector<int>> flow(n, vector<int>(n, 0));
        vector<int> parent(n, -1);
        int max_flow = 0;

        while (helper_funcs::find_augmenting_path(source, sink, n, parent, capacity, flow, adjacent)) {
            int path_flow = INF;
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                path_flow = min(path_flow, capacity[u][v] - flow[u][v]);
            }

            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                flow[u][v] += path_flow;
                flow[v][u] -= path_flow;
            }

            max_flow += path_flow;
        }

        return {max_flow, flow};
    }

    // **Finds the reachable set S in the residual graph**
    vector<int> find_min_cut(int source, int n, const vector<vector<int>>& capacity, 
                             const vector<vector<int>>& flow, unordered_map<int, vector<int>>& adjacent) {
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(source);
        visited[source] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adjacent[u]) {
                if (!visited[v] && capacity[u][v] > flow[u][v]) {  // If residual capacity exists
                    visited[v] = true;
                    q.push(v);
                }
            }
        }

        // Collect all reachable nodes
        vector<int> S;
        for (int i = 0; i < n; i++) {
            if (visited[i]) {
                S.push_back(i);
            }
        }
        return S;
    }
}

int main() {
    int n, m, source, sink;
    cin >> n >> m >> source >> sink;

    vector<vector<int>> capacity(n, vector<int>(n, 0));
    unordered_map<int, vector<int>> adjacent;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        capacity[u][v] += w;  // Add capacity for directed edge
        adjacent[u].push_back(v);
        adjacent[v].push_back(u);  // Needed for residual graph
    }

    // Compute max flow
    auto [max_flow, flow] = tree_solver::edmonds_karp(n, source, sink, capacity, adjacent);

    // Find the minimum cut
    vector<int> S = tree_solver::find_min_cut(source, n, capacity, flow, adjacent);

    // Output the size of S and the nodes in S
    cout << S.size() << endl;
    for (int node : S) {
        cout << node << endl;
    }

    return 0;
}
