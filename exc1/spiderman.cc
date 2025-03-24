#include <iostream>
#include <vector>
#include <climits>
#include <unordered_map>
#include <algorithm>
#include <iterator>
using namespace std;

// Custom hash function for pair<int, int>
struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
};

int climb(vector<int> const& steps, int index, int curr_height, int max_height, int curr_path,
          unordered_map<pair<int, int>, int PairHash>& memo, int& best_path, int& min_max_height) {

    if (index == steps.size() - 1) {
        if (curr_height - steps[index] == 0 && max_height < min_max_height) {
            best_path = (curr_path << 1);
            min_max_height = max_height;
            return max_height;
        }
        return INT_MAX;
    }

    //Need to prune something more???

    //We've already been here, doesn't matter if we had different paths
    auto state = make_pair(index, curr_height);
    if (memo.find(state) != memo.end() && memo[state] <= max_height) {
        return INT_MAX;
    }

    int lh_max = INT_MAX;
    int rh_max = INT_MAX;

    if (0 <= curr_height - steps[index]) {
        lh_max = climb(steps, index + 1, curr_height - steps[index], max_height,
                       (curr_path << 1), memo, best_path, min_max_height);
    }

    //if we've already found a better alternative no need to go down path
    if (curr_height + steps[index] < min_max_height) {
        rh_max = climb(steps, index + 1, curr_height + steps[index],
                       max(curr_height + steps[index], max_height), (curr_path << 1) | 1, memo, best_path, min_max_height);
    }

    int result = min(lh_max, rh_max);
    memo[state] = result; 
    return result;
}

// Decoding the binary path
void decodePath(int path, int steps_size) {
    for (int i = steps_size - 1; i >= 0; --i) {
        if ((path & (1 << i)) != 0) {
            cout << 'U';
        } else {
            cout << 'D';
        }
    }
    cout << endl;
}

int main() {
    int n, m;
    cin >> n;

    while (n--) {
        cin >> m;
        vector<int> steps(m);
        for (int i = 0; i < m; ++i) {
            cin >> steps[i];
        }
        int best_path = 0;
        int max = INT_MAX;
        unordered_map<pair<int, int>, int, PairHash> memo;
        int result = climb(steps, 0, 0, 0, 0, memo, best_path, max);

        if (result == INT_MAX) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            decodePath(best_path, m);
        }
    }

    return 0;
}
