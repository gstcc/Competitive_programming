
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int memo[31][31][10001]; // memo[start][n][current_sum]

unsigned int countWinningCombinations(
    const vector<int>& tiles,
    int start,
    int n,
    int t,
    int current_sum = 0
) {
    if (n == 0) return (current_sum == t) ? 1 : 0;
    if (start > tiles.size() - n) return 0;

    int& res = memo[start][n][current_sum];
    if (res != -1) return res;

    unsigned int count = 0;
    for (int i = start; i <= tiles.size() - n; ++i) {
        if (current_sum + tiles[i] > t) continue;
        count += countWinningCombinations(tiles, i + 1, n - 1, t, current_sum + tiles[i]);
    }

    return res = count;
}


unsigned long long binomial(int m, int n) {
    if (n > m - n) n = m - n; // Use symmetry
    unsigned long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= (m - i + 1);
        result /= i;
    }
    return result;
}

int main() {
    int nr_of_games, m, n, t;
    cin >> nr_of_games;
    for (int j = 1; j <= nr_of_games; j++) {
        cin >> m;
        vector<int> tiles(m);
        for (int i = 0; i < m; i++) {
            cin >> tiles[i];
        }
        sort(tiles.begin(), tiles.end());

        cin >> n >> t;

        // Reset memo table to -1 before each game
        memset(memo, -1, sizeof(memo));

        unsigned int wins = countWinningCombinations(tiles, 0, n, t);
        unsigned long long total = binomial(m, n);
        unsigned long long losses = total - wins;

        cout << "Game " << j << " -- " << wins << " : " << losses << endl;
    }
    return 0;
}
