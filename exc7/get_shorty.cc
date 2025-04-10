#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <utility>
#include <vector>
#include <unordered_map>
#include <queue>
#include <cmath>
#include <climits>

using namespace std;

/*Find the distance between s and all nodes, the queries are then just lookups*/
void dijkstra(vector<double>& price_to_reach_nodes, unordered_map<int, vector<pair<int, double>>>& outgoing_edges, int start, int n) {
    std::priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq; // Min heap
    
    // Initialize distances
    price_to_reach_nodes.assign(n, INT_MAX);
    price_to_reach_nodes[start] = 0;
    
    pq.push({0, start}); // Start with the source node

    while (!pq.empty()) {
        auto [cost, node] = pq.top();
        pq.pop();

        // Ignore outdated (invalid) entries in the priority queue
        if (cost > price_to_reach_nodes[node]) continue;

        for (auto [neighbor, weight] : outgoing_edges[node]) {
            double new_cost = cost + weight;

            if (new_cost < price_to_reach_nodes[neighbor]) {
                price_to_reach_nodes[neighbor] = new_cost;
                pq.push({new_cost, neighbor}); // Push updated cost
            }
        }
    }
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        if (n==0 && m==0) break;
        int x, y;
        double f;
        unordered_map<int, vector<pair<int, double>>> outgoind_edges;
        for (int i=0; i<m; i++) {
            cin >> x >> y >> f;
            outgoind_edges[x].push_back({y, -(log(f))});
            outgoind_edges[y].push_back({x, -(log(f))});
        }
        vector<double> price_to_reach_nodes(n);
        dijkstra(price_to_reach_nodes, outgoind_edges, 0, n);
        std::cout << fixed << setprecision(4) << exp(-price_to_reach_nodes[n-1]) << std::endl;
    }
}


