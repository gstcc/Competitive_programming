#include <iostream>
#include <vector>
#include <unordered_map>
#include "tree_solver.cc"
#include <algorithm>
#include <numeric>

using namespace std;


int main() {

    int n, m;
    while (cin >> n >> m && (n || m)) {
        unordered_map<int, vector<pair<int, int>>> graph;
        
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            graph[u].emplace_back(v, w);
            graph[v].emplace_back(u, w);
        }

        auto [total, edges] = tree_solver::prims(graph, n);

        if (total == -1) {
            cout << "Impossible\n";
        } else {
            cout << total << "\n";
            for (auto [u, v] : edges) {
                cout << u << " " << v << "\n";
            }
        }
    }
    return 0;
}