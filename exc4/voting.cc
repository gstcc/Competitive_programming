#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>
#include <cstring>
#include <string>

using namespace std;

int memo[100][9]; //index, curr_state will contain the result

map<int, string> ind_to_str {
    {0, "NNN"},
    {1, "NNY"},
    {2, "NYN"},
    {3, "NYY"},
    {4, "YNN"},
    {5, "YNY"},
    {6, "YYN"},
    {7, "YYY"}
};

void read_preferences(int m, vector<vector<int>>& priests) {
    for(int i{0}; i<m; i++) {
        vector<int> tmp(8);
        for(int p{0}; p<8; p++){
            cin >> tmp[p];
            tmp[p]--;
        }
        priests.push_back(tmp);
    }
}

int flip_val(int curr, int index) {
    return curr ^ 1 << index;
}

int simulate_round(vector<vector<int>> const& priests, int index, int curr_state) {
    if (index == priests.size()) {
        return curr_state;
    }

    //memoization
    if (memo[index][curr_state] != -1) {
        return memo[index][curr_state];
    }

    //recursive case
    int best_element = simulate_round(priests, index+1, flip_val(curr_state, 0));
    for (int i{1}; i<3; i++) {
        int res = simulate_round(priests, index+1, flip_val(curr_state, i));
        if (priests[index][res] < priests[index][best_element]) {
            best_element = res;
        }
    }
    return memo[index][curr_state] = best_element;
}

void start_problem() {
    int m;
    cin >> m;
    vector<vector<int>> priests;
    read_preferences(m, priests);  
    memset(memo, -1, sizeof(memo));
    int result = simulate_round(priests, 0, 0);
    std::cout << ind_to_str[result] << std::endl; 
}

int main() {
    int n;
    cin >> n;
    for(int i{0}; i<n; i++) {
        start_problem();
    }
}