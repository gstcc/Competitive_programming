'''
Gustav Carlsson (gusca083)
Finds the area of a polygon using the shoelace formula.
The formula calculates a polygon's area by summing the signed 
areas of trapezoids formed between consecutive vertices 
Timecomplexity: O(n), space O(n)
'''
def calc_area(sholace):
    two_a = sholace[0][-1] * sholace[1][0] - sholace[0][0] * sholace[1][-1]
    for i in range(0, len(sholace[0]) - 1):
        two_a += (sholace[0][i] * sholace[1][i + 1] - sholace[0][i + 1] * sholace[1][i])
    
    return two_a / 2

def main():
    n = 0
    while True:
        n = int(input())
        if n == 0:
            break
        shoelace = [[], []]
        for _ in range(0, n):
            x, y = map(float, input().split())
            shoelace[0].append(x)
            shoelace[1].append(y)
        area = calc_area(shoelace)
        if area < 0:
            print("CW", abs(area))
        else:
            print("CCW", abs(area))
if __name__ == "__main__":
    main()
