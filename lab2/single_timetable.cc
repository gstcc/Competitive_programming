#include <vector>
#include <iostream>
#include <unordered_map>
#include "combined.cc"

using namespace std;



int main() {
    int n, m, q, s, u, v, t0, P, d;
    while(cin >> n >> m >> q >> s) {
        if (!(n||m||q||s)) break;

        unordered_map<int, vector<int>> outgoing_edges;
        //Containing the edges between nodes, assuming that each pair of nodes can have multiple edges
        unordered_map<pair<int, int>, vector<vector<int>>, pair_hash> edges; 

        for (int i{0}; i<m; i++) {
            cin >> u >> v >> t0 >> P >> d;
            outgoing_edges[u].push_back(v);
            edges[{u, v}].push_back({t0, P, d});
        }

        auto dist = graph_solver::time_table(outgoing_edges, edges, s, n);

        int node;
        for (int i{0}; i<q; i++) {
            cin >> node;
            if (dist[node] == INF) {
                std::cout << "Impossible" << endl;
            } else {
                std::cout << dist[node] << endl;
            }
        }
        std::cout << endl;

    }
}