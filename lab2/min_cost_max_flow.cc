#include <iostream>
#include <vector>
#include <unordered_map>
#include "tree_solver.cc"

using namespace std;

int main() {
    int n, m, source, sink;
    cin >> n >> m >> source >> sink;

    vector<vector<int>> capacity(n, vector<int>(n, 0));
    vector<vector<int>> cost(n, vector<int>(n, 0));
    unordered_map<int, vector<int>> adjacent;

    for (int i = 0; i < m; i++) {
        int u, v, cap, c;
        cin >> u >> v >> cap >> c;
        capacity[u][v] = cap;
        cost[u][v] = c;
        capacity[v][u] = 0; // Reverse edge starts with zero capacity
        cost[v][u] = -c; // Reverse edge has negative cost for residual graph
        adjacent[u].push_back(v);
        adjacent[v].push_back(u); // Needed for residual graph traversal
    }

    pair<int, int> result = tree_solver::min_cost_max_flow(n, source, sink, capacity, cost, adjacent);
    cout << result.first << " " << result.second << endl;

    return 0;
}
