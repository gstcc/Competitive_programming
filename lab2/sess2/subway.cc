#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <cmath>
#include <climits>

using namespace std;

typedef pair<int, int> Coord; // (x, y) coordinates

// Custom hash function for unordered_map with pair<int, int>
struct pair_hash {
    template <typename T1, typename T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ (h2 << 1); // Combine the hashes
    }
};

// Calculate Euclidean distance between two points
double distance(Coord a, Coord b) {
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

/* Dijkstra's Algorithm */
void dijkstra(unordered_map<Coord, vector<pair<Coord, double>>, pair_hash>& graph, 
              unordered_map<Coord, double, pair_hash>& min_time, 
              Coord start) {
    
    priority_queue<pair<double, Coord>, vector<pair<double, Coord>>, greater<pair<double, Coord>>> pq;
    pq.push({0, start});
    min_time[start] = 0;

    while (!pq.empty()) {
        auto [cost, node] = pq.top();
        pq.pop();

        if (cost > min_time[node]) continue;

        for (auto [neighbor, weight] : graph[node]) {
            double new_cost = cost + weight;
            if (new_cost < min_time[neighbor]) {
                min_time[neighbor] = new_cost;
                pq.push({new_cost, neighbor});
            }
        }
    }
}

int main() {
    // Read home & school coordinates
    int home_x, home_y, school_x, school_y;
    cin >> home_x >> home_y >> school_x >> school_y;
    Coord home = {home_x, home_y}, school = {school_x, school_y};

    // Read walking & subway speeds
    double walk_speed = 10;
    double subway_speed = 40;

    // Read subway lines
    vector<vector<Coord>> lines;
    int x, y;
    while (true) {
        vector<Coord> line;
        while (cin >> x >> y) {
            if (x == -1 && y == -1) break;
            line.push_back({x, y});
        }
        if (line.empty()) break;
        lines.push_back(line);
    }

    unordered_map<Coord, vector<pair<Coord, double>>, pair_hash> graph;
    vector<Coord> locations = {home, school};

    // Build subway edges
    for (const auto& line : lines) {
        for (size_t i = 0; i < line.size() - 1; i++) {
            Coord stop1 = line[i], stop2 = line[i + 1];
            double dist = distance(stop1, stop2);
            double time = dist / subway_speed;
            graph[stop1].emplace_back(stop2, time);
            graph[stop2].emplace_back(stop1, time);
            locations.push_back(stop1);
            locations.push_back(stop2);
        }
    }

    // Add walking edges
    int n = locations.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            Coord loc1 = locations[i], loc2 = locations[j];
            double walk_dist = distance(loc1, loc2);
            double walk_time = walk_dist / walk_speed;
            graph[loc1].emplace_back(loc2, walk_time);
            graph[loc2].emplace_back(loc1, walk_time);
        }
    }

    // Run Dijkstra's Algorithm
    unordered_map<Coord, double, pair_hash> min_time;
    for (const auto& loc : locations) {
        min_time[loc] = INT_MAX;
    }

    dijkstra(graph, min_time, home);

    // Print the shortest time to school (rounded to nearest minute)
    cout << round(min_time[school] * 60 / 1000) << endl;

    return 0;
}
