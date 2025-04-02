#include <iostream>
#include <vector>

const int INF = 1e9;

using namespace std;

const vector<pair<int, int>> directions = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};  // North, West, East, South

bool in_bounds(int x, int y, int H, int W) {
    return x >= 0 && x < H && y >= 0 && y < W;
}

char last_used = 'a';

char dfs(int x, int y, vector<vector<int>>& height_map, int H, int W, vector<vector<char>>& basins) {
    int lowest = INF;
    int lowest_x = -1, lowest_y = -1;
    for (auto [dx, dy] : directions) {
        int new_x = x+dx;
        int new_y = y+dy;
        if (!in_bounds(new_x, new_y, H, W) || height_map[x][y]<=height_map[new_x][new_y]) continue;
        if (height_map[new_x][new_y] < lowest) {
            lowest = height_map[new_x][new_y];
            lowest_x = new_x;
            lowest_y = new_y;
        }
    }

    //Could not find any lower around, we have reached a sink
    if(lowest_x==-1 && lowest_y==-1) {
        if (basins[x][y] != 0) return basins[x][y];
        return basins[x][y] = last_used++;
    } 

    //Assign the value of current pos to next basin we can find
    return basins[x][y] = dfs(lowest_x, lowest_y, height_map, H, W, basins);
 }

int main() {
    int T, H, W, n;
    cin >> T;
    for (int i{0}; i<T; i++) {
        cin >> H >> W;
        vector<vector<int>> height_map;
        for (int j{0}; j<H; j++) {
            vector<int> row;
            for (int k{0}; k<W; k++) {
                cin >> n;
                row.push_back(n);
            }
            height_map.push_back(row);
        }
        last_used = 'a';
        vector<vector<char>> basins(H, vector<char>(W, 0));
        for (int j = 0; j < H; j++) {
            for (int k = 0; k < W; k++) {
               if (basins[j][k]) continue;
               dfs(j, k, height_map, H, W, basins);
            }
        }

        cout << "Case #" << (i+1) << ":\n";
        for (int j = 0; j < H; j++) {
            for (int k = 0; k < W; k++) {
                if (k != 0) cout << " ";
                cout << basins[j][k];
            }
            cout << "\n";
        }


    }
}