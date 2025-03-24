#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>
#include <cstring>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;

int memo[11][22][22];
int timestamps[11][22][22];

struct pair_hash {
    template <typename T1, typename T2>
    std::size_t operator ( ) (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);  // Hash the first element
        auto h2 = std::hash<T2>{}(p.second); // Hash the second element
        // Combine the hashes using a bitwise XOR and shifting
        return h1 ^ (h2 << 1); 
    }
};

// 0<=x,y < n
int find_nr_of_moles(int start_x, int start_y, int time, int d, int moles_smacked, int n, int last) {
    if (time==0) { //base case we can place hammer wherever we want???
        int best = 0;
        for(int x{0}; x<n; x++) {
            for(int y{0}; y<n; y++) {
                int curr = find_nr_of_moles(x, y, time+1, d, 0, n, last);
                if (curr> best) {
                    best = curr;
                }
            }
        }
        return best;
    }

    if (time > last) {
        return moles_smacked;
    }

    if (memo[time][start_x][start_y] >= moles_smacked) { //no need to redo the same position of better was already found
        return -1;
    }
    
    //recursive case, we can move in a straight line at most d distance 
    
    memo[time][start_x][start_y] = moles_smacked;
    //Find all point's within d distance, and collect all of which are on the same line
    unordered_map<pair<int, int>, vector<pair<int, int>>, pair_hash> slopes;
    for(int dx{-d}; dx<=d; dx++) {
        for(int dy{-d}; dy<=d; dy++) {
            if (start_x+dx < 0 || start_x+dx >= n) break; //not valid, continue on with the next x
        
            if (0 <= start_y+dy && start_y+dy < n && dx*dx + dy*dy <= d*d) { 
                double slope = (dx == 0) ? std::numeric_limits<double>::infinity() : static_cast<double>(dy) / dx;
                slopes[{dx<0, slope}].push_back({start_x + dx, start_y + dy});
            }
        }
    }

    int best = 0;
    for (auto it = slopes.begin(); it != slopes.end(); ++it) {
        vector<pair<int, int>>& points = it->second;
        std::sort(points.begin(), points.end());
        int smacked = 0;
        for (auto pt = points.begin(); pt != points.end(); ++pt) {
            smacked += timestamps[time][pt->first][pt->second];
            int result = find_nr_of_moles(pt->first, pt->second, time+1, d, moles_smacked+smacked, n, last);
            if (result > best) {
                best = result;
            }
        }
    }
    return best;
}

int main() {
    int n, d, m;
    cin >> n >> d >> m;
    while(!(n==0 && d==0 && m==0)) {
        int x, y, t;
        memset(memo, -1, sizeof(memo));
        memset(timestamps, 0, sizeof(timestamps));
        int last = 0;
        for(int i{0}; i<m; i++) {
            cin >> x >> y >> t;
            if (t > last) {
                last = t;
            }
            timestamps[t][x][y] = 1;
        }
        std::cout << find_nr_of_moles(0, 0, 0, d, 0, n, last) << "\r\n";
        cin >> n >> d >> m;
    }   
}