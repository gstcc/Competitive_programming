#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <unordered_map>
#include "tree_solver.cc"

using namespace std;

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;

    vector<vector<int>> capacity(n, vector<int>(n, 0));
    unordered_map<int, vector<int>> adjacent;

    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        capacity[u][v] = c;
        adjacent[u].push_back(v);
        adjacent[v].push_back(u);

    }

    auto [max_flow, flow] = tree_solver::edmonds_karp(n, s, t, capacity, adjacent);

    // Count edges used in the flow
    int edge_count = 0;
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (flow[u][v] > 0) {
                edge_count++;
            }
        }
    }

    cout << n << " " << max_flow << " " << edge_count << endl;

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (flow[u][v] > 0) {
                cout << u << " " << v << " " << flow[u][v] << endl;
            }
        }
    }

    return 0;
}
