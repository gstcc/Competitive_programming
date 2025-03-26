#include <vector>
#include <iostream>
#include <climits>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <numeric>

const int INF = INT_MAX/2;

using namespace std;

struct pair_hash {
    template <typename T1, typename T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

namespace helper_funcs {

    
    bool find_augmenting_path(int source, int sink, int n, vector<int>& parent, const vector<vector<int>>& capacity, const vector<vector<int>>& flow, unordered_map<int, vector<int>>& adjacent) {
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(source);
        visited[source] = true;
        parent[source] = -1;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            //Could probably make this faster by instead just using a map with adjancent nodes from u
            for (int v : adjacent[u]) {
                if (!visited[v] && capacity[u][v] > flow[u][v]) {
                    parent[v] = u;
                    visited[v] = true;
                    q.push(v);
                    if (v == sink) return true;
                }
            }
        }
        return false;
    }

    bool find_cheapest_augmenting_path(int source, int sink, int n, vector<int>& parent, const vector<vector<int>>& capacity, const vector<vector<int>>& flow, const vector<vector<int>>& cost, vector<int>& dist, unordered_map<int, vector<int>>& adjacent) {
        vector<bool> in_queue(n, false);
        queue<int> q;
        fill(dist.begin(), dist.end(), INF);
        parent[source] = -1;
        dist[source] = 0;
        q.push(source);
        in_queue[source] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            in_queue[u] = false;

            for (int v : adjacent[u]) {
                if (capacity[u][v] > flow[u][v] && dist[u] + cost[u][v] < dist[v]) {
                    dist[v] = dist[u] + cost[u][v];
                    parent[v] = u;
                    if (!in_queue[v]) {
                        q.push(v);
                        in_queue[v] = true;
                    }
                }
            }
        }
        return parent[sink] != -1;
    }
};


namespace tree_solver {



    /*NOT CURRENTLY WORKING*/
    pair<int, int> min_cost_max_flow(int n, int source, int sink, vector<vector<int>>& capacity, vector<vector<int>>& cost, unordered_map<int, vector<int>>& adjacent) {
        vector<vector<int>> flow(n, vector<int>(n, 0));
        vector<int> parent(n, -1);
        vector<int> dist(n, INF);
        int max_flow = 0, min_cost = 0;

        while (helper_funcs::find_cheapest_augmenting_path(source, sink, n, parent, capacity, flow, cost, dist, adjacent)) {
            int path_flow = INF;
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                path_flow = min(path_flow, capacity[u][v] - flow[u][v]);
            }

            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                flow[u][v] += path_flow;
                flow[v][u] -= path_flow;
                min_cost += path_flow * cost[u][v];
            }

            max_flow += path_flow;
        }

        return {max_flow, min_cost};
    }

    /*
    * edmond-karps method for finding maximum flow in graph
    * graph is all outgoing edges from a node u, and their capacity
    */
   pair<int, vector<vector<int>>> edmonds_karp(int n, int source, int sink, vector<vector<int>>& capacity, unordered_map<int, vector<int>>& adjacent) {
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

    /**
     * Prim's Algorithm for finding Minimum Spanning Tree (MST)
     * 
     * Time Complexity: O(E log V) using binary min-heap
     *   - Processes each of E edges once
     *   - Each heap operation takes O(log V) time
     * 
     * Space Complexity: O(V + E)
     *   - O(V) for visited/parent/key arrays and priority queue
     *   - O(E) for graph adjacency list storage
     * 
     * Finds MST in an undirected, connected, weighted graph:
     * 1. Grows tree by always adding minimum-weight edge
     * 2. Returns {total_weight, edges} or {-1, {}} if disconnected
     */
    pair<int, vector<pair<int, int>>> prims(unordered_map<int, vector<pair<int, int>>>& graph, int n) {
        vector<bool> visited(n, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        vector<int> parent(n, -1);
        vector<int> key(n, INF);
        int total_weight = 0;
        vector<pair<int, int>> mst;

        key[0] = 0;
        pq.push({0, 0});

        while (!pq.empty()) {
            auto [current_key, u] = pq.top();
            pq.pop();

            if (visited[u]) continue;
            visited[u] = true;
            total_weight += current_key;

            if (parent[u] != -1) {
                mst.push_back({min(parent[u], u), max(parent[u], u)});
            }

            for (auto [v, weight] : graph[u]) {
                if (!visited[v] && weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                    pq.push({weight, v});
                }
            }
        }

        if (mst.size() != n-1) {
            return {-1, {}};
        }

        sort(mst.begin(), mst.end());
        return {total_weight, mst};
    }
}


