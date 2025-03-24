#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

// Edge structure represents an edge in the flow network
struct Edge {
    int to;         // Neighboring vertex
    int reverse;    // Index of the reverse edge
    long long flow; // Current flow along the edge
    long long capacity; // Maximum capacity of the edge
    long long cost; // Cost per unit flow along the edge

    Edge(int to, int reverse, long long capacity, long long cost = 0) :
        to(to), reverse(reverse), flow(0), capacity(capacity), cost(cost) {}
};

// Graph class represents a graph of flow edges
class Graph : public vector<vector<Edge>> {
public:
    Graph(size_t n) : vector<vector<Edge>>(n) {}

    void addEdge(int from, int to, long long capacity, long long cost = 0) {
        operator[](from).emplace_back(to, operator[](to).size(), capacity, cost);
        operator[](to).emplace_back(from, operator[](from).size() - 1, 0, -cost);
    }
};

// Edmonds-Karp implementation using BFS
class EdmondsKarp {
public:
    Graph &graph;
    int numVertices, source, sink;
    vector<int> level;
    vector<vector<Edge>::iterator> iterators;

    EdmondsKarp(Graph &graph, int source, int sink) :
        graph(graph), numVertices(graph.size()), source(source), sink(sink), level(numVertices, -1), iterators(numVertices) {}

    // BFS to find the augmenting path
    bool bfs() {
        fill(level.begin(), level.end(), -1);
        level[source] = 0;
        queue<int> q;
        q.push(source);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto &&e : graph[u]) {
                if (e.capacity > e.flow && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }

        return level[sink] != -1;
    }

    // DFS to find the maximum flow from source to sink
    long long dfs(int u, long long flow) {
        if (u == sink) return flow;
        for (auto &e = iterators[u]; e != graph[u].end(); ++e) {
            if (e->capacity > e->flow && level[u] < level[e->to]) {
                long long availableFlow = min(flow, e->capacity - e->flow);
                long long pushedFlow = dfs(e->to, availableFlow);
                if (pushedFlow > 0) {
                    e->flow += pushedFlow;
                    graph[e->to][e->reverse].flow -= pushedFlow;
                    return pushedFlow;
                }
            }
        }
        return 0;
    }

    long long run() {
        long long maxFlow = 0;
        while (bfs()) {
            for (int u = 0; u < numVertices; ++u) {
                iterators[u] = graph[u].begin();
            }
            long long flow;
            while ((flow = dfs(source, LLONG_MAX)) > 0) {
                maxFlow += flow;
            }
        }
        return maxFlow;
    }
};

int main() {
    int T;
    cin >> T;

    while (T--) {
        int numResidents;
        cin >> numResidents;

        // Initialize counters and mappings
        int partyCount = 0, clubCount = 0;
        unordered_map<string, int> partyMap, clubMap;
        vector<string> residentNames, partyNames, clubNames;
        vector<int> residentToParty;
        vector<vector<int>> residentToClubs;

        // Input the residents and their information
        for (int i = 0; i < numResidents; ++i) {
            string resident, party;
            cin >> resident >> party;
            residentNames.push_back(resident);

            // Assign a unique ID to each party
            int partyID = 0;
            if (partyMap.find(party) != partyMap.end()) {
                partyID = partyMap[party];
            } else {
                partyID = partyCount++;
                partyNames.push_back(party);
                partyMap[party] = partyID;
            }

            residentToParty.push_back(partyID);

            // Input the clubs the resident belongs to
            int numClubs;
            cin >> numClubs;
            residentToClubs.push_back(vector<int>());
            while (numClubs--) {
                string club;
                cin >> club;

                // Assign a unique ID to each club
                int clubID = 0;
                if (clubMap.find(club) != clubMap.end()) {
                    clubID = clubMap[club];
                } else {
                    clubID = clubCount++;
                    clubNames.push_back(club);
                    clubMap[club] = clubID;
                }

                residentToClubs.back().push_back(clubID);
            }
        }

        // Upper bound on party representatives
        int upperBound = (clubCount - 1) / 2;

        if (upperBound == 0) {
            cout << "Impossible." << endl;
        } else {
            Graph graph(2 + clubCount + numResidents + partyCount);
            int source = clubCount + numResidents + partyCount;
            int sink = source + 1;

            // Connect parties to the sink
            for (int i = 0; i < partyCount; ++i) {
                graph.addEdge(clubCount + numResidents + i, sink, upperBound);
            }

            // Connect residents to their party
            for (int i = 0; i < numResidents; ++i) {
                graph.addEdge(clubCount + i, clubCount + numResidents + residentToParty[i], 1);
            }

            // Connect residents to their clubs
            for (int i = 0; i < numResidents; ++i) {
                for (int clubID : residentToClubs[i]) {
                    graph.addEdge(clubID, clubCount + i, 1);
                }
            }

            // Connect source to clubs
            for (int i = 0; i < clubCount; ++i) {
                graph.addEdge(source, i, 1);
            }

            EdmondsKarp edmondsKarp(graph, source, sink);
            long long flow = edmondsKarp.run();

            // If not all clubs are matched, it's impossible
            if (flow < clubCount) {
                cout << "Impossible." << endl;
            } else {
                vector<int> clubAssignments(clubCount, -1);
                for (int i = 0; i < clubCount; ++i) {
                    for (auto &edge : graph[i]) {
                        if (edge.flow > 0 && edge.to >= clubCount && edge.to < clubCount + numResidents) {
                            clubAssignments[i] = edge.to - clubCount;
                        }
                    }
                }

                // Output the assignments
                for (int i = 0; i < clubCount; ++i) {
                    cout << residentNames[clubAssignments[i]] << " " << clubNames[i] << endl;
                }
            }
        }

        if (T > 0) cout << endl;
    }

    return 0;
}
