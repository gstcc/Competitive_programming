#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct pair_hash {
    template <typename T1, typename T2>
    std::size_t operator ( ) (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);  // Hash the first element
        auto h2 = std::hash<T2>{}(p.second); // Hash the second element
        return h1 ^ (h2 << 1); 
    }
};

vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};


vector<pair<pair<int, int>, int>> tmp(pair<int, int> node1, vector<string> const& rows, int nr_of_rows, int nr_of_cols, unordered_map<pair<int, int>, int, pair_hash>& nodes, int nr_of_nodes) {
    queue<pair<pair<int, int>, int>> q;
    vector<vector<bool>> visited(nr_of_rows, vector<bool>(nr_of_cols, false)); // 2D boolean array
    vector<pair<pair<int, int>, int>> distances;

    q.push({node1, 0});
    visited[node1.second][node1.first] = true;

    while (!q.empty()) {
        auto [pos, turn] = q.front();
        q.pop();

        if ((rows[pos.second][pos.first] == 'A' || rows[pos.second][pos.first] == 'S') && pos != node1) {
            distances.push_back({{nodes[node1], nodes[pos]}, turn});
        }

        if (distances.size() == nr_of_nodes-1) break;


        for (auto [dx, dy] : directions) {
            int new_x = pos.first + dx;
            int new_y = pos.second + dy;

            if (new_y >= 0 && new_y < nr_of_rows && new_x >= 0 && new_x < nr_of_cols &&
                rows[new_y][new_x] != '#' && !visited[new_y][new_x]) {
                
                q.push({{new_x, new_y}, turn + 1});
                visited[new_y][new_x] = true;
            }
        }
    }
    return distances;
}

struct DisjointSet {
    vector<int> parent, rank;
    
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;  // Initialize each node as its own parent
    }

    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]); // Path compression
        return parent[u];
    }

    bool unionSet(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU == rootV)
            return false;  // Already in the same set

        // Union by rank
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
        return true;
    }
};

int kruskal(vector<pair<pair<int, int>, int>> &edges, int numNodes) {
    // Step 1: Sort edges by weight
    sort(edges.begin(), edges.end(), [] (auto lh, auto rh) {return lh.second < rh.second;});

    DisjointSet dsu(numNodes);
    vector<pair<int, pair<int, int>>> mst; // Stores MST edges
    int totalCost = 0;

    // Step 2: Process edges in increasing order of weight
    for (auto &edge : edges) {
        int weight = edge.second;
        int u = edge.first.first;
        int v = edge.first.second;

        if (dsu.unionSet(u, v)) {  // If adding this edge doesn't form a cycle
            mst.push_back({weight, {u, v}});
            totalCost += weight;
            if (mst.size() == numNodes - 1)
                break;
        }
    }

    return totalCost;
}

int main() {
    int n, nr_of_rows, cols;
    cin >> n;
    for (; n>0; n--) {
        //read info
        cin >> cols >> nr_of_rows;
        vector<string> rows(nr_of_rows);
        vector<pair<int, int>> nodes;
        string t;
        getline(cin, t);
        unordered_map<pair<int, int>, int, pair_hash> indexes;
        //read all rows, save where each A and S is
        for (int r{0}; r<nr_of_rows; r++) {
            getline(cin, rows[r], '\n');
            for (int c{0}; c<cols; c++) {
                if (rows[r][c] == 'A' || rows[r][c] == 'S') {
                    nodes.push_back({c, r});
                    indexes[{c, r}] = nodes.size()-1;
                }
            }
        }

        if (nodes.size() <= 1) {
            cout << 0 << endl;
            continue;
        }

        //Find the distance between each point
        //Contains the indexes of the two nodes, and the distance between them
        vector<pair<pair<int, int>, int>> distances;
        for (int i{0}; i<nodes.size()-1; i++) {
            auto dist = tmp(nodes[i], rows, nr_of_rows, cols, indexes, nodes.size());
            distances.insert(distances.end(), dist.begin(), dist.end());
        }

        // Find mst with kurskas
        cout << kruskal(distances, nodes.size()) << endl;
    }
}