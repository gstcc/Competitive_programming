#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include "../lab2/tree_solver.cc"  

using namespace std;

int main() {
    int N, M;
    while (cin >> N) {
        if (N == -1) break;
        cin >> M;

        vector<int> standings(N + 1); // 1-based
        for (int i = 1; i <= N; ++i) {
            cin >> standings[i];
        }

        vector<pair<int, int>> matches;
        for (int i = 0; i < M; ++i) {
            int a, b;
            cin >> a >> b;
            matches.emplace_back(a, b);
        }

        // Track match results by original order
        vector<int> result(M, -1);

        // Calculate max points team N can reach
        int final_points_N = standings[N];
        vector<pair<int, int>> filtered_matches;
        vector<int> filtered_indices;

        for (int i = 0; i < M; ++i) {
            int a = matches[i].first;
            int b = matches[i].second;

            if (a == N) {
                final_points_N += 2;
                result[i] = 0; // team N wins
            } else if (b == N) {
                final_points_N += 2;
                result[i] = 2; // team N wins
            } else {
                filtered_matches.emplace_back(a, b);
                filtered_indices.push_back(i); // Track original index
            }
        }

        // Check if any team already has more points than team N can achieve
        bool impossible = false;
        for (int i = 1; i <= N; ++i) {
            if (i != N && standings[i] >= final_points_N) {
                impossible = true;
                break;
            }
        }
        if (impossible) {
            cout << "NO" << endl;
            continue;
        }

        // Build flow network
        int match_count = filtered_matches.size();
        int team_count = N - 1; // excluding team N
        int total_nodes = 1 + match_count + team_count + 1; // source, matches, teams, sink
        int source = 0;
        int sink = total_nodes - 1;

        vector<vector<int>> capacity(total_nodes, vector<int>(total_nodes, 0));
        unordered_map<int, vector<int>> adj;

        auto team_index = [&](int team) {
            if (team == N) throw runtime_error("Team N should not be in the flow network");
            return (team < N ? team - 1 : team - 2) + 1 + match_count;
        };

        // Connect source to each match node
        for (int i = 0; i < match_count; ++i) {
            int match_node = 1 + i;
            capacity[source][match_node] = 2;
            adj[source].push_back(match_node);
            adj[match_node].push_back(source);

            int a = filtered_matches[i].first;
            int b = filtered_matches[i].second;

            int a_node = team_index(a);
            int b_node = team_index(b);

            capacity[match_node][a_node] = 2;
            capacity[match_node][b_node] = 2;

            adj[match_node].push_back(a_node);
            adj[match_node].push_back(b_node);
            adj[a_node].push_back(match_node);
            adj[b_node].push_back(match_node);
        }

        // Connect team nodes to sink with allowed points
        for (int i = 1; i <= N; ++i) {
            if (i == N) continue;
            int team_node = team_index(i);
            int max_gain = final_points_N - 1 - standings[i];
            if (max_gain < 0) max_gain = 0;

            capacity[team_node][sink] = max_gain;
            adj[team_node].push_back(sink);
            adj[sink].push_back(team_node);
        }

        // Compute max flow
        auto [max_flow, flow] = tree_solver::edmonds_karp(total_nodes, source, sink, capacity, adj);
        int required_flow = 2 * match_count;

        if (max_flow == required_flow) {
            // Convert flow into match outcomes
            for (int i = 0; i < match_count; ++i) {
                int match_node = 1 + i;
                int a = filtered_matches[i].first;
                int b = filtered_matches[i].second;

                int a_node = team_index(a);
                int b_node = team_index(b);

                int fa = flow[match_node][a_node];
                int fb = flow[match_node][b_node];

                int outcome = -1;
                if (fa == 2 && fb == 0) outcome = 0;
                else if (fa == 1 && fb == 1) outcome = 1;
                else if (fa == 0 && fb == 2) outcome = 2;
                else outcome = 1; // fallback to draw

                result[filtered_indices[i]] = outcome;
            }

            // Output results in input order
            for (int i = 0; i < M; ++i) {
                cout << result[i];
                if (i != M - 1) cout << " ";
            }
            cout << endl;
        } else {
            cout << "NO" << endl;
        }

        // Read blank line after each block
        string dummy;
        getline(cin, dummy); // consume leftover newline
        getline(cin, dummy);
    }

    return 0;
}
