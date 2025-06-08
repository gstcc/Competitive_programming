
#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <sstream>

using namespace std;

const int INF = INT_MAX/2; 

vector<int> reconstructPath(int target, int start, const vector<int>& parent) {
    vector<int> path;
    if (parent[target] == -1) return path;  // No path
    if (parent[target] == -2) return {-2};  // In negative cycle

    for (int at = target; at != -1; at = parent[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    if (path.front() != start) return {};  // Path does not originate from source
    return path;
}


pair<vector<long long>, vector<int>> bellmanFord(int V, int start, const vector<vector<int>>& edges) {
    vector<long long> dist(V, INF);
    vector<int> parent(V, -1);  // To reconstruct paths
    dist[start] = 0;

    for (int i = 0; i < V - 1; ++i) {
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            if (dist[u] != INF && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }

    vector<bool> inNegativeCycle(V, false);
    for (int i = 0; i < V; ++i) {
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            if (dist[u] != INF && dist[v] > dist[u] + w) {
                dist[v] = -INF;
                inNegativeCycle[v] = true;
            }
            if (inNegativeCycle[u]) inNegativeCycle[v] = true;
        }
    }

    for (int i = 0; i < V; ++i) {
        if (inNegativeCycle[i]) {
            dist[i] = -INF;
            parent[i] = -2;  // Mark path as invalid due to negative cycle
        }
    }

    return {dist, parent};
}

int main() {
    int n, m, q, s;
    while (cin >> n >> m >> q >> s, n || m || q || s) {
        vector<vector<int>> edges(m);
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            edges[i] = {u, v, w};
        }

        auto dist = bellmanFord(n, s, edges);

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
