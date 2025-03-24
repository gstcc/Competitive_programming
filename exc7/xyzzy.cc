#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include "graph.h"

using namespace std;

int main() {    
    int n;
    while (cin >> n) {
        if (n == -1) break;

        vector<int> energy(n + 1, INT_MIN);  // Track maximum energy we can have at each room
        vector<Weighted_Edge> edges;
        vector<int> predecestors(n + 1, -1);  // Store predecessors for path reconstruction
        
        energy[1] = 100; // Start energy is 100

        int w, to, nr_of_edges;
        for (int i = 1; i <= n; i++) {
            cin >> w >> nr_of_edges;
            for (int j = 0; j < nr_of_edges; j++) {
                cin >> to;
                edges.push_back({i, to, w});
            }
        }

        // Bellman-Ford to find the max energy path
        for (int i = 0; i < n - 1; i++) {
            for (auto const& edge : edges) {
                if (energy[edge.from] != INT_MIN && energy[edge.from] + edge.w > energy[edge.to]) {
                    energy[edge.to] = energy[edge.from] + edge.w;
                    predecestors[edge.to] = edge.from;
                }
            }
        }

        // **Check if we can reach the last room with valid energy**
        if (energy[n] > 0) {
            int v = n;
            bool valid_path = true;
            while (v != 1 && predecestors[v] != -1) {
                if (energy[predecestors[v]] < 0) {  
                    valid_path = false;  // If any room in the path has negative energy, it's invalid
                    break;
                }
                v = predecestors[v];
            }
            if (valid_path) {
                cout << "winnable" << endl;
                continue;
            }
        }

        // **Detect Positive Energy Cycle that Reaches `n`**
        vector<bool> in_cycle(n + 1, false);
        for (auto const& edge : edges) {
            if (energy[edge.from] != INT_MIN && energy[edge.from] + edge.w > energy[edge.to]) {
                in_cycle[edge.to] = true;
            }
        }

        // **BFS to check if any cycle node can reach `n`**
        vector<bool> visited(n + 1, false);
        queue<int> q;
        for (int i = 1; i <= n; i++) {
            if (in_cycle[i]) {
                q.push(i);
                visited[i] = true;
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == n) {  
                cout << "winnable" << endl;
                goto next_case;
            }
            for (auto const& edge : edges) {
                if (edge.from == u && !visited[edge.to]) {
                    q.push(edge.to);
                    visited[edge.to] = true;
                }
            }
        }

        // If no valid path or cycle leads to `n`, it's hopeless
        cout << "hopeless" << endl;
        
    next_case:
        continue;
    }

    return 0;
}
