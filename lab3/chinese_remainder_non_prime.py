'''
Gustav Carlsson (gusca083)
Finds a solution to a system of two modular congruences using the generalized Chinese Remainder Theorem.
solves a Diophantine equation with extended Euclidean algorithm.
Returns no solution if the system is inconsistent.

Time complexity: O(log(n1) + log(n2)), space: constant
'''

from math import gcd

def extended_gcd(a, b):
    if b == 0:
        return a, 1, 0
    g, x1, y1 = extended_gcd(b, a % b)
    x = y1
    y = x1 - (a // b) * y1
    return g, x, y

def crt_general(a1, n1, a2, n2):
    g, p, q = extended_gcd(n1, n2)
    if (a2 - a1) % g != 0:
        return None, None  # No solution

    lcm = n1 * n2 // g
    x = (a1 + (a2 - a1) // g * p * n1) % lcm
    return x, lcm

def main():
    T = int(input())
    for _ in range(T):
        a1, n1, a2, n2 = map(int, input().split())
        x, mod = crt_general(a1, n1, a2, n2)
        if x is None:
            print("no solution")
        else:
            print(x, mod)

if __name__ == "__main__":
    main()

