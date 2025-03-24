#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;
const int SCALE = 1e6;


bool can_win(bool turn, vector<int64_t> const& fs, int64_t x, unordered_map<int64_t, bool>& memo, int64_t goal) {
    if (x >= goal) {
        return true;
    }

    if (memo.find(x) != memo.end()) {
        return memo[x];
    }

    for(auto el: fs) {
        int64_t next_x = x * el;
        if (next_x >= goal) {
            return memo[x] = false;
        }
        if (can_win(!turn, fs, next_x, memo, goal)) {
            return memo[x] = false;
        }
    }
    return memo[x] = true;
}

void test(bool turn) {
    double x, k;
    cin >> x >> k;
    vector<int64_t> fs(k);
    double f;
    unordered_map<int64_t, bool> memo;
    double tmp{x};
    for(int i{0}; i < k; i++) {
        cin >> f;
        fs[i] = static_cast<int64_t>((1/f)*SCALE);
        tmp *= (1/f);
    }
    int64_t goal = static_cast<int64_t>(round(tmp * SCALE)); //Convert to int with 6 digits precision
    std::cout << goal << std::endl;
    for(auto el : fs) {
        std::cout << el << ", ";
    }
    std::cout << std::endl;
    std::sort(fs.begin(), fs.end());
    fs.erase(unique(fs.begin(), fs.end()), fs.end());
    if (can_win(turn, fs, static_cast<int64_t>(x*SCALE), memo, goal)) {
        std::cout << "Mikael" << std::endl;
    } else {
        std::cout << "Nils" << std::endl;
    }
}

int main() {
    int n;
    cin >> n;
    for(int i{0}; i < n; i++) {
        test(i%2==0);
    }
}