#include <vector>
#include <queue>
#include <limits>
#include <iostream>
#include <unordered_map>

using namespace std;

const int INF = numeric_limits<int>::max();

// Dijkstra-based function to find the shortest path with minimum cost
bool dijkstra(int n, int source, int sink, vector<int>& parent, vector<vector<int>>& capacity, 
              vector<vector<int>>& cost, vector<vector<int>>& flow, unordered_map<int, vector<int>>& adj, vector<int>& dist) {
    fill(dist.begin(), dist.end(), INF);
    fill(parent.begin(), parent.end(), -1);
    vector<bool> in_queue(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    
    dist[source] = 0;
    pq.push({0, source});
    
    while (!pq.empty()) {
        int d, u;
        tie(d, u) = pq.top(); pq.pop();
        
        if (in_queue[u]) continue;
        in_queue[u] = true;
        
        for (int v : adj[u]) {
            if (capacity[u][v] - flow[u][v] > 0) { 
                int new_dist = dist[u] + cost[u][v];
                if (new_dist < dist[v]) {
                    dist[v] = new_dist;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }
    return parent[sink] != -1;
}

pair<int, int> min_cost_max_flow(int n, int source, int sink, vector<vector<int>>& capacity, 
                                 vector<vector<int>>& cost, unordered_map<int, vector<int>>& adj) {
    vector<vector<int>> flow(n, vector<int>(n, 0));
    vector<int> parent(n);
    vector<int> dist(n);
    int max_flow = 0, min_cost = 0;

    while (dijkstra(n, source, sink, parent, capacity, cost, flow, adj, dist)) {
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
        capacity[v][u] = 0; 
        cost[v][u] = -c; 
        adjacent[u].push_back(v);
        adjacent[v].push_back(u); 
    }
    auto max_flow = min_cost_max_flow(n, source, sink, capacity, cost, adjacent);

    std::cout << max_flow.first << " " << max_flow.second << std::endl;

    return 0;
}
