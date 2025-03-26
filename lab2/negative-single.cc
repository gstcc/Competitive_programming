#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include "combined.cc"

using namespace std;



int main() {
    int n, m, q, s;
    while (cin >> n >> m >> q >> s, n || m || q || s) {
        vector<vector<int>> edges(m);
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            edges[i] = {u, v, w};
        }

        auto dist = graph_solver::bellmanFord(n, s, edges);

        stringstream output;
        while (q--) {
            int node;
            cin >> node;
            if (dist[node] == -INF) {
                output << "-Infinity\n";
            } else if (dist[node] == INF) {
                output << "Impossible\n";
            } else {
                output << dist[node] << "\n";
            }
        }
        cout << output.str();
        if (n || m || q || s) cout << endl;  // Blank line between test cases
    }
}