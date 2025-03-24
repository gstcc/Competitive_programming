#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>

using namespace std;

void solve(unsigned long long candies, vector<unsigned long long>& childNeeds) {
    unsigned long long totalAnger = 0;

    unsigned long long totalNeed = std::accumulate(childNeeds.begin(), childNeeds.end(), 0ULL);

    unsigned long long candiesLeft = totalNeed - candies;

    sort(childNeeds.begin(), childNeeds.end());

    for (size_t i = 0; i < childNeeds.size(); ++i) {
        unsigned long long candiesTaken = min(childNeeds[i], candiesLeft / (childNeeds.size() - i));
        totalAnger += candiesTaken * candiesTaken;
        candiesLeft -= candiesTaken;
    }

    cout << totalAnger << endl;
}

int main() {
    unsigned long long candies, children;
    cin >> candies >> children;

    vector<unsigned long long> childNeeds(children);

    for (unsigned long long i = 0; i < children; ++i) {
        cin >> childNeeds[i];
    }

    solve(candies, childNeeds);

    return 0;
}
