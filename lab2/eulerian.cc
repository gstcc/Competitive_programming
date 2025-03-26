#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iterator>


using namespace std;

bool path_exists(unordered_map<int, vector<int>> const& outgoing_edges, vector<int> const& in_degrees, int& start, int& end) {
    int omi = 0, imo = 0;

    for (int u = 0; u < in_degrees.size(); u++) {
        int out_degree = outgoing_edges.count(u) ? outgoing_edges.at(u).size() : 0;  // Handle missing nodes

        if (out_degree - in_degrees[u] == 1) {
            omi++;
            start = u;
        } else if (in_degrees[u] - out_degree == 1) {
            imo++;
            end = u;
        } else if (out_degree != in_degrees[u]) {
            return false;
        }
    }
    return omi <= 1 && imo <= 1;
}

vector<int> find_Eulerian_path(unordered_map<int, vector<int>>& outgoing_edges, int odd_node) {
    int start = odd_node;
    if (start == -1) {
        for (auto& [u, v] : outgoing_edges) {
            if (!v.empty()) {
                start = u;  // Choose any node with outgoing edges
                break;
            }
        }
    }

    vector<int> stack{start}, path; 
    while (!stack.empty()) {
        int curr = stack.back();
        if (outgoing_edges[curr].empty()) {
            path.push_back(curr);
            stack.pop_back();
        } else {
            int next = outgoing_edges[curr].back();
            stack.push_back(next);
            outgoing_edges[curr].pop_back();
        }
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    int n, m, u, v;
    while (cin >> n >> m) {
        if (!(n || m)) break;
        
        unordered_map<int, vector<int>> outgoing_edges;
        vector<int> in_degrees(n, 0);
        
        for (int i = 0; i < m; i++) {
            cin >> u >> v;
            outgoing_edges[u].push_back(v);
            if (v >= n) {  // Ensure we resize in_degrees correctly
                in_degrees.resize(v + 1, 0);
            }
            in_degrees[v]++;
        }

        int start = -1, end = -1;
        if (!path_exists(outgoing_edges, in_degrees, start, end)) {
            cout << "Impossible" << endl;
        } else {
            auto path = find_Eulerian_path(outgoing_edges, start == -1 ? 0 : start);
            if (path.size() - 1 != m) {  // Ensure all edges are used
                cout << "Impossible" << endl;
            } else {
                copy(path.begin(), path.end(), ostream_iterator<int>{cout, " "});
                cout << endl;
            }
        }
    }
}
