#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

int find_cheapest_path(const vector<vector<pair<int, int>>>& graph,
                       const vector<int>& fuel_prices,
                       int start, int end, int tank_size) {
    int n = graph.size();
    vector<vector<int>> dist(n, vector<int>(tank_size + 1, INF));  
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;

    dist[start][0] = 0;
    pq.push({0, {start, 0}});  

    while (!pq.empty()) {
        auto [cost, state] = pq.top();
        int city = state.first, fuel_left = state.second;
        pq.pop();

        if (city == end) return cost;

        if (cost > dist[city][fuel_left]) continue;

        if (fuel_left < tank_size) {
            int newCost = cost + fuel_prices[city];
            if (newCost < dist[city][fuel_left + 1]) {
                dist[city][fuel_left + 1] = newCost;
                pq.push({newCost, {city, fuel_left + 1}});
            }
        }

        for (auto& [neighbor, road_length] : graph[city]) {
            if (fuel_left >= road_length) {
                int newFuel = fuel_left - road_length;
                if (cost < dist[neighbor][newFuel]) {
                    dist[neighbor][newFuel] = cost;
                    pq.push({cost, {neighbor, newFuel}});   
                }
            }
        }
    }

    return -1;
}

int main() {
    int n, m, u, v, d, q, s, e, c;
    cin >> n >> m;

    vector<int> fuel_prices(n);
    for (int i = 0; i < n; i++) {
        cin >> fuel_prices[i];
    }

    vector<vector<pair<int, int>>> graph(n); 
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> d;
        graph[u].emplace_back(v, d);
        graph[v].emplace_back(u, d);
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> c >> s >> e;
        int cost = find_cheapest_path(graph, fuel_prices, s, e, c);
        if (cost == -1) {
            cout << "impossible" << endl;
        } else {
            cout << cost << endl;
        }
    }

    return 0;
}
