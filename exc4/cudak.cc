#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

long long dp[16][135][2];

// Digit DP function
long long countNumbers(string &num, int pos = 0, int sum = 0, bool tight = true) {
    if (sum < 0) {
        return 0;
    }
    if (pos == num.size()) {
        return sum == 0;  // If end is reached, check if sum == 0
    }

    if (dp[pos][sum][tight] != -1) {
        return dp[pos][sum][tight];
    }

    long long res = 0;
    int limit = tight ? (num[pos] - '0') : 9;  // Restrict digits if tight

    for (int d = 0; d <= limit; ++d) {
        res += countNumbers(num, pos + 1, sum - d, tight && (d == limit));
    }

    dp[pos][sum][tight] = res; 
    return res;
}

// Function to count numbers from 1 to X with sum S
long long countUpTo(long long X, int S) {
    if (X < 0) return 0;
    string num = to_string(X);
    memset(dp, -1, sizeof(dp));
    return countNumbers(num, 0, S, true);
}

int main() {
    long long A, B;
    int S;
    cin >> A >> B >> S;

    long long result = countUpTo(B, S) - countUpTo(A - 1, S);
    cout << result << endl;
    // cout << find_first(A, B, S) << endl;
}
