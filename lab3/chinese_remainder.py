'''
Gustav Carlsson (gusca083)
Finds the chinese remainder theorem according following the formula x=(a1*m1*m1^-1 + a2*m2*m2^-1) mod M
Timecomplexity O(log(n1)+log(n2)), space constant 
'''
def euclidean(a, n):
    n0 = n
    x0, x1 = 0, 1

    if n == 1:
        return 1

    while a > 1:
        q = a // n
        a, n = n, a % n
        x0, x1 = x1 - q * x0, x0

    if x1 < 0:
        x1 += n0

    return x1

# Calculates the chinese remainder of two coprime numbers a1, a2 modulo n1, n2
def chinese_remainder(a1, n1, a2, n2):
    M = n1 * n2
    m1 = M // n1
    m2 = M // n2
    m1p = euclidean(m1, n1)
    m2p = euclidean(m2, n2)
    x = ((a1 * m1 % M) * m1p + (a2 * m2 % M) * m2p) % M
    return x, M
    
 

def main():
    T = int(input())
    for _ in range(T):
        a1, n1, a2, n2 = map(int, input().split())
        x, M = chinese_remainder(a1, n1, a2, n2)
       print(x, M)

if __name__ == "__main__":
    main()
