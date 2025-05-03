/*
 * Gustav Carlsson (gusca083)
 * Time complexity per operation: O(log(n)), total O(t * log(n)), where n is the modulus and t is the number of queries
 * Space complexity: O(1)
 * Performs modular arithmetic (addition, subtraction, multiplication, division) under modulo n
 * Division uses the modular inverse via the Extended Euclidean Algorithm
 * Assumes that N > 1 and that y is coprime to N for division operations (i.e., gcd(y, n) == 1)
 */


#include <cmath>
#include <iostream>
#include <numeric>
#include <string>

using namespace std;
//finds x^-1 mod n, assuming a and n are coprime
long long modInverse(long long a, long long n)
{
    long long n0 = n, t, q;
    long long x0 = 0, x1 = 1;

    if (n == 1)
        return 0;

    while (a > 1)
    {
        q = a / n;
        t = n;

        n = a % n;
        a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += n0;

    return x1;
}
long long mod(long long x, long long n)
{
    return (x % n + n) % n;
}
void addition(long long x, long long y, long long n, bool isSubtraction)
{
    cout << mod(mod(x, n) + mod(y, n), n) << endl;
}

void division(long long x, long long y, long long n)
{
    if (gcd(y, n) != 1) {
        cout << -1 << endl;
        return;
    }
    cout << mod(mod(x, n) * modInverse(y, n), n) << endl;
}

void multiplication(long long x, long long y, long long n)
{
    cout << mod(mod(x, n) * mod(y, n), n) << endl;
}

int main()
{
    long long n, t, x, y;
    string op;
    while (cin >> n >> t)
    {
        if (!(n || t))
            break;
        while (t--)
        {
            cin >> x >> op >> y;
            if (op == "+")
                addition(x, y, n, false);
            else if (op == "-")
                addition(x, -y, n, true);
            else if (op == "/")
                division(x, y, n);
            else
                multiplication(x, y, n);
        }
    }
}

