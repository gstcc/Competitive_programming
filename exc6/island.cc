#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <limits>
#include <queue>
#include <iomanip>
#include <tuple>

using namespace std;

const double EPSILON = 1e-9;

struct point {
    double x, y;

    bool operator==(const point& other) const {
        return fabs(x - other.x) < EPSILON && fabs(y - other.y) < EPSILON;
    }

    bool operator<(const point& other) const {
        return tie(x, y) < tie(other.x, other.y);
    }
};

struct PointHash {
    size_t operator()(const point& p) const {
        auto hash1 = hash<double>{}(p.x);
        auto hash2 = hash<double>{}(p.y);
        return hash1 ^ (hash2 * 31);
    }
};

double distance(point p1, point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

int main() {
    int n, m;
    double x, y;
    cin >> n;
    while (n--) {
        cin >> m;
        vector<point> points(m);
        for (int j = 0; j < m; j++) {
            cin >> x >> y;
            points[j] = {x, y};
        }

        unordered_map<point, vector<pair<point, double>>, PointHash> edges;
        unordered_map<point, double, PointHash> key;
        unordered_map<point, bool, PointHash> visited;

        for (int i = 0; i < m - 1; i++) {
            for (int j = i + 1; j < m; j++) {
                double dist = distance(points[i], points[j]);
                edges[points[i]].push_back({points[j], dist});
                edges[points[j]].push_back({points[i], dist});
            }
        }

        struct Compare {
            bool operator()(const pair<double, point>& a, const pair<double, point>& b) {
                return a.first > b.first; // Min-heap
            }
        };

        priority_queue<pair<double, point>, vector<pair<double, point>>, Compare> pq;
        point start = points[0];

        for (const auto& p : points) {
            key[p] = numeric_limits<double>::max();
            visited[p] = false;
        }

        key[start] = 0.0;
        pq.push({0.0, start});
        double total_cost = 0.0;
        vector<point> mstSet;

        while (!pq.empty()) {
            auto [cost, pos] = pq.top();
            pq.pop();

            if (visited[pos]) continue;

            visited[pos] = true;
            total_cost += cost;
            mstSet.push_back(pos);

            if (mstSet.size() == points.size()) {
                cout << std::fixed << setprecision(4) << total_cost << endl;
                break;
            }

            for (auto& [neighbor, dist] : edges[pos]) {
                if (!visited[neighbor] && dist < key[neighbor]) {
                    key[neighbor] = dist;
                    pq.push({dist, neighbor});
                }
            }
        }
    }
}
