#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int memo[1001][1001];

int solve(vector<int>& plates, int index, int current_weight) {
    if (index >= plates.size()) {
        return current_weight; // Base case: No more plates left
    }

    if (current_weight >= 1000) {
        return current_weight;
    }

    if (memo[index][current_weight] != -1) {
        return memo[index][current_weight];  // Use cached result
    }

    int include = solve(plates, index + 1, current_weight + plates[index]);
    int without = solve(plates, index + 1, current_weight);

    if (abs(1000 - include) < abs(1000 - without)) {
        return memo[index][current_weight] = include;
    } else if (abs(1000 - include) > abs(1000 - without)) {
        return memo[index][current_weight] = without;
    } else {
        return memo[index][current_weight] = max(include, without);
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> plates(n);

    for (int i = 0; i < n; i++) {
        cin >> plates[i];   
    }
    sort(plates.begin(), plates.end())
    memset(memo, -1, sizeof(memo));  // Initialize memo table
    int best_weight = solve(plates, 0, 0);
    cout << best_weight << endl; 
}
