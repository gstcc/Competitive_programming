#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <cstring>

using namespace std;

struct pair_hash {
    template <typename T1, typename T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ (h2 << 1); // Combine the hashes
    }
};

int visited[2000];

int main() {
    int n, m, a, b, k, g, L, intersec1, intersec2;
    cin >> n >> m >> a >> b >> k >> g;

    vector<int> georges_visits(g);
    fill(visited, visited + 2000, -1);

    // Map contains the street and the timespan that it's occupied
    unordered_map<pair<int, int>, pair<int, int>, pair_hash> occupied_during; 
    unordered_map<pair<int, int>, int, pair_hash> traversal_time;
    unordered_map<int, vector<pair<int, int>>> roads;

    for (int i = 0; i < g; i++) {
        cin >> georges_visits[i];
    }

    // Read all streets
    for (int i = 0; i < m; i++) {
        cin >> intersec1 >> intersec2 >> L;
        traversal_time[{intersec1, intersec2}] = L;
        traversal_time[{intersec2, intersec1}] = L;
        roads[intersec1].push_back({intersec2, L});
        roads[intersec2].push_back({intersec1, L});
    }   

    int time = 0;
    // Map out when roads are occupied by George
    for (int i = 0; i < g - 1; i++) {
        int start = georges_visits[i], end = georges_visits[i + 1];
        occupied_during[{start, end}] = {time, time + traversal_time[{start, end}]};
        occupied_during[{end, start}] = {time, time + traversal_time[{start, end}]}; // Add reverse direction
        time += traversal_time[{start, end}];
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    time = k;
    pq.push({time, a}); 

    while (!pq.empty()) {
        auto [curr_time, pos] = pq.top();
        pq.pop();

        if (visited[pos] != -1 && curr_time >= visited[pos]) continue;
        visited[pos] = curr_time;

        if (pos == b) {
            cout << curr_time - k << endl;
            return 0;
        }

        for (auto [end, travel_time] : roads[pos]) {
            int new_time = curr_time + travel_time;

            if (occupied_during.count({pos, end})) {
                auto [start_time, end_time] = occupied_during[{pos, end}];
                if (curr_time >= start_time && curr_time < end_time) {
                    new_time = end_time + travel_time;
                }
            }

            pq.push({new_time, end});
        }
    }

    return 0;
}
