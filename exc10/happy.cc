#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

vector<int> find_all_primes(int limit = 10000000) {
    vector<int> primes;
    vector<int> spf(limit, 0);
    for (int i = 2; i < limit; i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > spf[i] || p * i >= limit) break;
            spf[p * i] = p;
        }
    }
    return primes;
}

int sumOfSquares(int n) {
    int sum = 0;
    while (n > 0) {
        int digit = n % 10;     // Get the last digit
        sum += digit * digit;   // Square and add
        n /= 10;                // Remove the last digit
    }
    return sum;
}

int main() {
    int K, P, m;
    cin >> P;
    vector<bool> is_prime(10000, false);
    vector<int> primes = find_all_primes(10000);
    for (int i : primes) {
        is_prime[i] = true;
    }
    while(P--) {
        cin >> K >> m;
        if (!is_prime[m]) {
            std::cout << K << " " << m << " " << "NO" << std::endl;
            continue;
        }
        unordered_set<int> visited;
        int tmp = m;
        while(tmp!=1 || !visited.count(tmp)) {
            tmp = sumOfSquares(tmp);
            visited.insert(tmp);
        }
        if (tmp==1) {

        } else {}

        
    }
}
