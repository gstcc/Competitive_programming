#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

const int MODULO = 1000000000;

bool reachable[2][10000];
int state[10000];
int memo[10000];
bool very_big=false;

void mark_reachable(int dir, int node, unordered_map<int, vector<int>>& neighbours) {
    if (!reachable[dir][node]) {
        reachable[dir][node] = true;
        for (int u : neighbours[node]) {
            mark_reachable(dir, u, neighbours);
        }
    }
}

int dfs(int node, unordered_map<int, vector<int>>& neighbours) {
    if (state[node] == 1) return memo[node]; // Already computed
    if (state[node] == 2) return -1;  // Cycle detected (infinite paths)

    state[node] = 2;
    memo[node] = (node == 1 ? 1 : 0);

    for (int u : neighbours[node]) {
        if (reachable[0][u] && reachable[1][u]) {
            int res = dfs(u, neighbours);
            if (res == -1) return -1;
            if (memo[node]+res >= MODULO) very_big=true;
            memo[node] = (memo[node] + res) % MODULO;
        }
    }

    state[node] = 1; // Mark node as "fully processed"
    return memo[node];
}

int main() {
    int N, M, start, end;
    cin >> N >> M;

    unordered_map<int, vector<int>> neighbours;
    unordered_map<int, vector<int>> reverse_neighbours;

    for (int i = 0; i < M; i++) {
        cin >> start >> end;
        neighbours[start - 1].push_back(end - 1);
        reverse_neighbours[end - 1].push_back(start - 1);
    }

    fill(&reachable[0][0], &reachable[0][0] + 2 * 10000, false);
    fill(state, state + 10000, 0);
    fill(memo, memo + 10000, 0);

    mark_reachable(0, 0, neighbours);
    mark_reachable(1, 1, reverse_neighbours);

    int res = dfs(0, neighbours);
    if (res == -1) {
        cout << "inf" << endl;
    } else if (very_big) {
        cout << setw(9) << setfill('0') << res << endl; 
    }
    else {
        cout << res % MODULO << endl;
    }
}
