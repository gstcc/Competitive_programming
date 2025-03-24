/*
    Gustav Carlsson (gusca083)
    Maximize the total value of items when you have a sack that can take a maximum weight of capacity
    and where each item has a weight and a value
    time-complexity: O(n^2)
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iterator>

using namespace std;


int knapsack[2001][2001]; 

void reconstruct_solution(vector<int> const& weights, int n, int capacity) {
    vector<int> selected;
    while(n > 0 && capacity > 0) {
        if (knapsack[n][capacity] == knapsack[n-1][capacity]) {
            n -= 1;
        } else {
            selected.push_back(n-1); //Used 1-based indexing before
            capacity -= weights[n];
            n -= 1;
        }
    }
    std::cout << selected.size() << std::endl;
    sort(selected.begin(), selected.end());
    copy(selected.begin(), selected.end(), ostream_iterator<int>{cout, " "});
    cout << endl;
}

int main() {
    int capacity, n;
    while(cin >> capacity >> n) {
        vector<int> values(n+1);
        vector<int> weights(n+1);
        int value, weight;
        for(int i{1}; i<=n; i++) {
            cin >> value >> weight;
            values[i] = value;
            weights[i] = weight;
        }
        memset(knapsack, 0, sizeof(knapsack));
        for(int i{1}; i<=n; i++) {
            for(int k{1}; k<=capacity; k++) {
                if (weights[i] > k) { //The new item's weight is more than the current capacity
                    knapsack[i][k] = knapsack[i-1][k];
                } else {
                    knapsack[i][k] = max(knapsack[i-1][k], knapsack[i-1][k-weights[i]] + values[i]);
                }
            }
        }
        reconstruct_solution(weights, n, capacity);
    }
}