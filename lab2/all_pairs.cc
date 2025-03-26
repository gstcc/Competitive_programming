#include <vector>
#include <iostream>
#include <climits>
#include <cmath>
#include "combined.cc"



int main() {

    int n, m, q;
    int u, v, w;
    while(cin >> n >> m >> q) {
        if (!(n||m||q)) break; //if all are zero end

        std::vector<std::vector<int>> graph;
        for (int i{0}; i<m; i++) {
            std::cin >> u >> v >> w;
            graph.push_back({u, v, w});
        }

        //Get the distance between all nodes
        auto dist = graph_solver::floyd_warshall(graph, n);

        int from, to;
        for (auto i{0}; i<q; i++) {
            std::cin >> from >> to;
            if (dist[from][to] == INF) {
                std::cout << "Impossible" << std::endl;
            } else if (dist[from][to] == -INF) {
                std::cout << "-Infinity" << std::endl;
            }
            else {
                std::cout << dist[from][to] << std::endl;
            }
        }        
        std::cout << std::endl;

    }
    
}