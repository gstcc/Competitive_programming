#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

size_t int_pow(size_t base, int exp) {
    size_t result = 1;
    while (exp--) result *= base;
    return result;
}

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

vector<pair<unsigned long long, int>> factorize(unsigned long long a, const vector<int>& primes) {
    vector<pair<unsigned long long, int>> result;
    for (int p : primes) {
        if (1ULL * p * p > a) break;
        if (a % p == 0) {
            int count = 0;
            while (a % p == 0) {
                a /= p;
                ++count;
            }
            result.push_back({p, count});
        }
    }
    if (a > 1) result.push_back({a, 1});
    return result;
}

vector<size_t> find_divisors(const vector<pair<unsigned long long, int>>& factors) {
    vector<size_t> result{1};
    for (auto [prime, exponent] : factors) {
        size_t size = result.size();
        for (int i = 1; i <= exponent; i++) {
            for (size_t j = 0; j < size; j++) {
                result.push_back(result[j] * int_pow(prime, i));
            }
        }
    }
    return result;
}

size_t eulers_totient(size_t a, const vector<int>& primes) {
    size_t result = 1;
    auto factors = factorize(a, primes);
    for (auto [prime, exp] : factors) {
        result *= (prime - 1);
        result *= int_pow(prime, exp - 1);
    }
    return result;
}

int main() {
    int T;
    size_t N;
    cin >> T;
    auto primes = find_all_primes();
    while (T--) {
        cin >> N;
        auto factors = factorize(N, primes);
        auto divs = find_divisors(factors);
        size_t sum = 0;
        for (auto d : divs) {
            sum += eulers_totient(N / d + 1, primes);
        }
        cout << sum << endl;
    }
}

