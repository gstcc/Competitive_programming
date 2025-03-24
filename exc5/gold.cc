#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

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


int traverse_board(int start_x, int start_y, vector<vector<char>> const& board, unordered_map<pair<int, int>, bool, pair_hash>& visited) {
    if (visited[make_pair(start_x, start_y)]) {
        return 0;
    }
    visited[make_pair(start_x, start_y)] = true;
    int total = board[start_y][start_x] == 'G' ? 1 : 0;;

    for(auto dir : directions) {
        if (board[start_y+dir.second][start_x+dir.first] == 'T') { // If we're near a trap, stop moving and return
            return total;
        }
    }

    for(auto dir : directions) {
        if (board[start_y+dir.second][start_x+dir.first] != '#') { // As long as we're not moving into a wall
            total += traverse_board(start_x+dir.first, start_y+dir.second, board, visited);
        }
    }
    return total;
}


int main() {
    int w, h;
    cin >> w >> h;
    cin.ignore();
    string s;
    vector<vector<char>> board;
    unordered_map<pair<int, int>, bool, pair_hash> visited;
    int start_x, start_y = -1;
    for(int row{0}; row<h; row++) {
        cin >> s;
        vector<char> tmp;
        for(int i = 0; i < s.size(); ++i) {
            tmp.push_back(s[i]);
            visited[make_pair(i, row)] = false;
            if (s[i] == 'P') {
                start_x = i;
                start_y = row;
            }
        }
        board.push_back(tmp);
    }
    cout << traverse_board(start_x, start_y, board, visited) << endl;
}