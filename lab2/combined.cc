#include <vector>
#include <unordered_map>
#include <climits>
#include <queue>
#include <iostream>

const int INF = INT_MAX/2; //Changed from INT_MAX/3, to INT_MAX/2, might cause issues with accepted solutions 

using namespace std;


struct pair_hash {
    template <typename T1, typename T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ (h2 << 1); // Combine the hashes
    }
};

int find_wait_time(int curr_time, int t0, int P) {
    if (curr_time <= t0) 
        return t0;
    
    if (P==0) 
        return INF;

    return t0 + ((curr_time - t0 + P - 1) / P) * P;

}

namespace graph_solver {

    vector<int> time_table(unordered_map<int, vector<int>> & outgoing_edges, 
        unordered_map<pair<int, int>, vector<vector<int>>, pair_hash> & edges, int start, int n) {

        
        std::priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Min heap
        
        // Initialize distances
        vector<int> price_to_reach_nodes(n, INF);
        price_to_reach_nodes[start] = 0;
        
        pq.push({0, start}); // Start with the source node

        while (!pq.empty()) {
            auto [time, node] = pq.top();
            pq.pop();

            // Ignore outdated (invalid) entries in the priority queue
            if (time > price_to_reach_nodes[node]) continue;
            
            //Add all neighbours
            for (int neighbour : outgoing_edges[node]) {
                auto it = edges.find({node, neighbour});
                if (it != edges.end()) {
                    for (auto const& edge : it->second) {
                        int next_available = find_wait_time(time, edge[0], edge[1]);
                        if (next_available == INF) continue;

                        // int new_time = time+next_available+edge[2];
                        int new_time = max(price_to_reach_nodes[node], next_available) + edge[2];

                        if (new_time < price_to_reach_nodes[neighbour]) {
                            price_to_reach_nodes[neighbour]=new_time;
                            pq.push({new_time, neighbour});
                        }
                    } 
                }
            }
        }
        return price_to_reach_nodes;
    }

    /**
     * Single-source shortest paths with negative cycle detection.
     * Time: O(V*E), Space: O(V)
     * Returns distance array (-INF = negative cycle reachable).
     */
    vector<int> bellmanFord(int V, int start, const vector<vector<int>>& edges) {
        vector<int> dist(V, INF);
        dist[start] = 0;
    
        // Relax all edges (V-1 times)
        for (int i = 0; i < V-1; ++i) {
            for (const auto& edge : edges) {
                int u = edge[0], v = edge[1], w = edge[2];
                if (dist[u] != INF && dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                }
            }
        }
    
        // Detect negative cycles
        vector<bool> inNegativeCycle(V, false);
        for (int i = 0; i < V; ++i) {  // Run one more iteration to propagate negative cycles
            for (const auto& edge : edges) {
                int u = edge[0], v = edge[1], w = edge[2];
                if (dist[u] != INF && dist[v] > dist[u] + w) {
                    dist[v] = -INF;
                    inNegativeCycle[v] = true;
                }
                if (inNegativeCycle[u]) inNegativeCycle[v] = true;  // Propagate further
            }
        }
    
        // Mark all nodes reachable from a negative cycle as -INF
        for (int i = 0; i < V; ++i) {
            if (inNegativeCycle[i]) dist[i] = -INF;
        }   
    
        return dist;
    }

    /**
     * All-pairs shortest paths with negative cycle detection.
     * Time: O(V³), Space: O(V²)
     * Returns distance matrix (-INF = affected by negative cycle).
     */
    vector<vector<int>> floyd_warshall(vector<vector<int>> const& edges, int n) {
        vector<vector<int>> dist(n, vector<int>(n, INF));
        vector<bool> is_in_negative_cycle(n, false);
    
        // Initialize distances and next array
        for (int i = 0; i < n; i++) {
            dist[i][i] = 0;
        }
        
        for (auto const& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            
            if (u==v && w > 0) continue;
            
            dist[u][v] = min(w, dist[u][v]);
        }
    
        // Floyd-Warshall Algorithm
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] == INF || dist[k][j] == INF) continue;

                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
        
        // Check for negative cycles, and "propgate them"
        for(int k = 0; k < n; k++) {
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    if(dist[i][k] == INF || dist[k][j] == INF) continue;

                    if(dist[k][k] < 0) {
                        dist[i][j] = -INF;
                    }
                }
            }
        }
    
        return dist;
    }
    

}

