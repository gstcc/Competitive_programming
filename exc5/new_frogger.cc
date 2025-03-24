#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <cstring>

using namespace std;

bool visited[51][22][51];

vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, 0}, {0, -1}, {0, 1}};

bool occupied(vector<string> const& roads, int width, int height, int turn, int y, int x) {
    if (height % 2 == 0) {
        int offset = (y % 2 == 0) ? (width - (turn % width)) : (turn % width);
        return roads[y][(x + offset) % width] == 'X';
    } else {
        int offset = (y % 2 == 1) ? (width - (turn % width)) : (turn % width);
        return roads[y][(x + offset) % width] == 'X';
    }
    
}


int traverse_board(int startX, int endX, int height, int width, vector<string> const& roads, int max_turns) {
    memset(visited, 0, sizeof(visited));
    deque<pair<pair<int, int>, int>> q;

    q.push_back({{startX, height+1}, 0});

    while (!q.empty()) {
        auto [pos, turn] = q.front();
        q.pop_front();

        if (turn > max_turns) {
            return -1;
        }

        if ((pos.first==endX) && (pos.second==0)) {
            return turn;
        }

        for(auto [dx, dy] : directions)  {
            int new_x = pos.first+dx;
            int new_y = pos.second+dy;
            if (0 <= new_x && new_x < width && 0 <= new_y && new_y <= height+1 
                && !occupied(roads, width, height, turn+1, new_y, new_x) && !visited[new_x][new_y][(turn + 1) % width]) {
                    q.push_back({{new_x, new_y}, turn + 1});
                    visited[new_x][new_y][(turn + 1) % width] = true;
            }
        }
    }

    return -1;
}

int main () {
    int nCases;
    string s;    
    cin >> nCases;
    for (int i=0; i<nCases; i++) {
        vector<string> roads;
        int turns, height, width;
        cin >> turns >> height >> width;
        for (int j=0; j<height+2; j++) {
            cin >> s;
            roads.push_back(s);
        }
        int startX = roads.back().find("F");
        int endX = roads.front().find("G");
        int minTurns = traverse_board(startX, endX, height, width, roads, turns);
        if (minTurns>=0) {
            cout << "The minimum number of turns is " << minTurns << "." << endl;
        } else {
            cout << "The problem has no solution." << endl;
        }
    }
  }