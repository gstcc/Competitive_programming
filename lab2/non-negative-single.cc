/*
    Gustav Carlsson (gusca083)
    Using dijkstra's to find the distance from start to all nodes reachable from start and then just lookup for querries
    Time-complexity O((V+E)log(V)) (from dijkstra)
    Space-complexity is O(V+E+Q), where q are the number of queries
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>
#include <sstream>

using namespace std;

/*Find the distance between s and all nodes, the queries are then just lookups*/
void dijkstra(vector<int>& price_to_reach_nodes, unordered_map<int, vector<pair<int, int>>>& outgoing_edges, int start, int n, vector<int>& parent) {
    std::priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Min heap

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
            int new_cost = cost + weight;

            if (new_cost < price_to_reach_nodes[neighbor]) {
                price_to_reach_nodes[neighbor] = new_cost;
                parent[neighbor] = node; // Keep track of parent, so we can reconstruct path
                pq.push({new_cost, neighbor}); // Push updated cost
            }
        }
    }
}

int main() {
    int n, m, q, s;
    int u, v, w;
    while (cin >> n >> m >> q >> s) {
        if (!(n||m||q||s)) break;
        unordered_map<int, vector<pair<int, int>>> outgoing_edges; //outgoing edges for each node
        for (int i = 0; i < m; i++)
        {
            cin >> u >> v >> w;
            outgoing_edges[u].push_back({v, w});
            // outgoing_edges[v].push_back({u, w});
        }
        vector<int> price_to_reach_nodes(n, INT_MAX);
        vector<int> parent(n, -1);
        // price_to_reach_nodes[s] = 0;
        dijkstra(price_to_reach_nodes, outgoing_edges, s, n, parent);
        int node;
        stringstream output;
        for(int i=0; i<q; i++) {
            cin >> node;
            if (price_to_reach_nodes[node] != INT_MAX) {
                output << price_to_reach_nodes[node] << "\n";
            } else {
                output << "Impossible\n";
            }
        }
        cout << output.str() << endl;
    }
}
