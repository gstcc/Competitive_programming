#include <iostream>
#include <map>
#include <cmath>
using namespace std;

// Function to factorize m into prime powers
map<int, int> factorize(int m) {
    map<int, int> factors;
    for (int i = 2; i * 1LL * i <= m; ++i) {
        while (m % i == 0) {
            factors[i]++;
            m /= i;
        }
    }
    if (m > 1)
        factors[m]++;
    return factors;
}

// Count exponent of p in n! using Legendre’s formula
int count_p_in_factorial(int n, int p) {
    int count = 0;
    while (n > 0) {
        n /= p;
        count += n;
    }
    return count;
}

int main() {
    int m, n;
    while (cin >> n >> m) {
        if (m == 0) {
            cout << "0 does not divide " << n << "!" << endl;
            continue;
        }

        map<int, int> factors = factorize(m);
        bool divides = true;

        for (auto [prime, exponent] : factors) {
            int count_in_fact = count_p_in_factorial(n, prime);
            if (count_in_fact < exponent) {
                divides = false;
                break;
            }
        }

        if (divides)
            cout << m << " divides " << n << "!" << endl;
        else
            cout << m << " does not divide " << n << "!" << endl;
    }

    return 0;
}
