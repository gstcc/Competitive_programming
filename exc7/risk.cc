#include <queue>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <vector>
#include <climits>
using namespace std;

// Constants for maximum size and node count
#define MAX_SIZE 100
#define MAX_NODES (MAX_SIZE * 2 + 2)
typdef 

// Global variables for the algorithm (reduced scope to functions wherever possible)
int height[MAX_NODES];                  // Heights of nodes
int excess[MAX_NODES];                  // Excess flow in nodes
int position[MAX_NODES];                // Position of nodes in height groups
vector<pair<int, int>> adj[MAX_NODES];  // Adjacency list
vector<int> height_groups[MAX_NODES + 1]; // Height groups for Push-Relabel
pair<int, int>::iterator current_edge[MAX_NODES]; // Iterator for edges of nodes
int capacity[2 * MAX_SIZE * (MAX_SIZE - 1) + 6 * MAX_SIZE];  // Edge capacities
int saved_capacity[2 * MAX_SIZE * (MAX_SIZE - 1) + 6 * MAX_SIZE]; // Saved edge capacities
int edge_count;                         // Total number of edges
queue<int> active_nodes;                // Queue of active nodes

// Push-Relabel algorithm
int PushRelabel(int node_count, int source, int sink, vector<pair<int, int>> adj[], int capacity[], int edge_count) {
    // Initialize data structures
    memset(height, 0, sizeof(int) * node_count);
    memset(excess, 0, sizeof(int) * node_count);
    
    vector<vector<int>> height_groups(node_count + 1);
    vector<int> position(node_count, 0);
    vector<pair<int, int>::iterator> current_edge(node_count);

    // Setup initial states
    for (int i = 0; i < node_count; ++i) {
        height_groups[i].clear();
        current_edge[i] = adj[i].begin();
        if (i != source && i != sink) {
            position[i] = height_groups[0].size();
            height_groups[0].push_back(i);
        }
    }
    height_groups[node_count].clear();
    height[source] = node_count;

    // Preflow phase
    for (auto &it : adj[source]) {
        if (capacity[it.second] > 0) {
            excess[it.first] = capacity[it.second];
            excess[source] -= capacity[it.second];
            capacity[(it.second + edge_count) % (2 * edge_count)] += capacity[it.second];
            capacity[it.second] = 0;
            if (it.first != sink) {
                active_nodes.push(it.first);
            }
        }
    }

    int max_height = 0;
    // Push-Relabel phase
    while (!active_nodes.empty()) {
        int u = active_nodes.front();
        active_nodes.pop();

        // Push flow while excess flow exists
        while (excess[u] > 0) {
            if (current_edge[u] == adj[u].end()) {
                // Relabel operation
                int min_height = INT_MAX;
                for (auto &it : adj[u]) {
                    if (capacity[it.second] > 0) {
                        min_height = min(min_height, height[it.first]);
                    }
                }
                ++min_height;
                assert(min_height > height[u]);
                int old_height = height[u];
                height[u] = min_height;

                // Update height groups
                if (old_height <= node_count) {
                    auto it = height_groups[old_height].begin() + position[u];
                    swap(*it, height_groups[old_height].back());
                    position[*it] = position[u];
                    height_groups[old_height].pop_back();
                    if (min_height <= node_count) {
                        if (height_groups[min_height].empty()) {
                            assert(min_height == 1 + max_height);
                            ++max_height;
                        }
                        position[u] = height_groups[min_height].size();
                        height_groups[min_height].push_back(u);
                    }
                    if (old_height && height_groups[old_height].empty()) {
                        assert(old_height <= max_height);
                        for (int i = old_height + 1; i <= max_height; ++i) {
                            for (auto &it : height_groups[i]) {
                                height[it] = node_count + 1;
                                current_edge[it] = adj[it].begin();
                            }
                            height_groups[i].clear();
                        }
                        max_height = old_height - 1;
                    }
                }
                current_edge[u] = adj[u].begin();
            } else {
                // Push operation
                int v = current_edge[u]->first;
                if (capacity[current_edge[u]->second] > 0 && height[u] == height[v] + 1) {
                    if (excess[v] == 0 && v != source && v != sink) {
                        active_nodes.push(v);
                    }
                    int flow = min(excess[u], capacity[current_edge[u]->second]);
                    capacity[current_edge[u]->second] -= flow;
                    capacity[(current_edge[u]->second + edge_count) % (2 * edge_count)] += flow;
                    excess[u] -= flow;
                    excess[v] += flow;
                } else {
                    ++current_edge[u];
                }
            }
        }
    }

    return excess[sink];
}

// Main function
int main() {
    int test_cases, node_count;
    scanf("%d", &test_cases);
    assert(test_cases >= 1 && test_cases <= 100);

    while (test_cases--) {
        scanf("%d", &node_count);
        assert(node_count >= 1 && node_count <= MAX_SIZE);

        int troops[MAX_SIZE];
        char adjacency[MAX_SIZE][MAX_SIZE + 1];

        // Input troops data
        for (int i = 0; i < node_count; ++i) {
            scanf("%d", &troops[i]);
        }

        edge_count = 0;

        // Input adjacency matrix and validate input
        for (int i = 0; i < node_count; ++i) {
            scanf("%s", adjacency[i]);
            assert(adjacency[i][node_count] == 0 && adjacency[i][i] == 'N');
            for (int j = 0; j < node_count; ++j) {
                assert(adjacency[i][j] == 'Y' || adjacency[i][j] == 'N');
                if (j < i) {
                    assert(adjacency[i][j] == adjacency[j][i]);
                    if (adjacency[i][j] == 'Y') edge_count += 2;
                }
            }
        }

        edge_count += node_count * 3;
        int total_nodes = node_count * 2 + 2;
        
        // Clear adjacency lists
        for (int i = 0; i < total_nodes; ++i) adj[i].clear();

        // Initialize the graph
        int edge_index = 0;
        vector<int> special_edges;
        int total_troops = 0;

        // Build the flow network
        for (int i = 0; i < node_count; ++i) {
            if (troops[i] == 0) continue;

            // Add source to node flow
            if (troops[i] > 1) {
                adj[0].push_back(make_pair(i + node_count + 1, edge_index));
                saved_capacity[edge_index] = troops[i] - 1;
                adj[i + node_count + 1].push_back(make_pair(0, edge_index + edge_count));
                saved_capacity[edge_index + edge_count] = 0;
                ++edge_index;
            }

            total_troops += troops[i];
            adj[i + node_count + 1].push_back(make_pair(i + 1, edge_index));
            saved_capacity[edge_index] = troops[i];
            adj[i + 1].push_back(make_pair(i + node_count + 1, edge_index + edge_count));
            saved_capacity[edge_index + edge_count] = 0;
            ++edge_index;

            // Add internal edges
            bool has_outer = false;
            for (int j = 0; j < node_count; ++j) {
                if (adjacency[i][j] == 'Y') {
                    if (troops[j] == 0) has_outer = true;
                    else {
                        adj[i + 1].push_back(make_pair(j + node_count + 1, edge_index));
                        saved_capacity[edge_index] = troops[i];
                        adj[j + node_count + 1].push_back(make_pair(i + 1, edge_index + edge_count));
                        saved_capacity[edge_index + edge_count] = 0;
                        ++edge_index;
                    }
                }
            }

            // Handle outer edges
            if (has_outer) {
                special_edges.push_back(edge_index);
                adj[i + node_count + 1].push_back(make_pair(total_nodes - 1, edge_index));
                adj[total_nodes - 1].push_back(make_pair(i + node_count + 1, edge_index + edge_count));
                ++edge_index;
            }
        }

        assert(!special_edges.empty() && edge_index <= edge_count);

        // Perform binary search for maximum flow
        int low = 0, high = total_troops / special_edges.size();
        while (low < high) {
            int mid = (low + high + 1) / 2;
            memcpy(capacity, saved_capacity, sizeof(int) * edge_count * 2);

            // Set special edges capacity
            for (auto &it : special_edges) {
                capacity[it] = mid;
                capacity[it + edge_count] = 0;
            }

            // Check for feasible flow
            if (PushRelabel(total_nodes, 0, total_nodes - 1, adj, capacity, edge_count) == special_edges.size() * mid)
                low = mid;
            else
                high = mid - 1;
        }

        printf("%d\n", low + 1);
    }
    return 0;
}
