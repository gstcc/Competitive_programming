#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;

struct Edge {
    int u, v, weight;
};

pair<int, vector<Edge>> prims(int start, unordered_map<int, vector<pair<int, int>>>& graph, int n, unordered_set<int>& insecure, vector<int>& best) {
    vector<bool> visited(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<int> parent(n, -1);
    vector<int> key(n, INF);
    int total_weight = 0;
    vector<Edge> mst;

    key[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [curr_weight, u] = pq.top();
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;
        total_weight += curr_weight;

        if (parent[u] != -1) {
            mst.push_back({parent[u], u, curr_weight});
        }

        for (auto [v, weight] : graph[u]) {
            if (!visited[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
                pq.push({weight, v});
            }
        }
    }

    return {total_weight, mst};
}

int main() {
    int n, m, p;
    cin >> n >> m >> p;
    
    unordered_map<int, vector<pair<int, int>>> graph;
    unordered_set<int> insecure;
    vector<int> best(n, INF);
    int x, y, w;

    for (int i = 0; i < p; i++) {
        cin >> x;
        insecure.insert(x - 1);
    }

    int start = -1;
    
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> w;
        x--; y--;

        if (insecure.count(x) && insecure.count(y)) continue;
        
        if (insecure.count(x)) {
            best[x] = min(best[x], w);
            continue;
        }
        if (insecure.count(y)) {
            best[y] = min(best[y], w);
            continue;
        }

        graph[x].push_back({y, w});
        graph[y].push_back({x, w});

        if (start == -1) start = x;
    }

    if (start == -1) {
        cout << "impossible\n";
        return 0;
    }

    auto [cost, mst] = prims(start, graph, n, insecure, best);
    
    for (int i = 0; i < n; ++i) {
        if (insecure.count(i)) {
            if (best[i] == INF) {
                cout << "impossible\n";
                return 0;
            }
            cost += best[i];
        }
    }
    
    cout << cost << endl;
    return 0;
}