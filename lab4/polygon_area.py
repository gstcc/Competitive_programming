"""
Gustav Carlsson (gusca083)
Finds the area of a polygon using the shoelace formula.
The formula calculates a polygon's area by summing the signed
areas of trapezoids formed between consecutive vertices
Timecomplexity: O(n), space O(n)
"""

from math import sqrt, acos


# Point class as requried by lab4, assumes that we are in a ON-based system, since the angle wouldn't work otherwise
class Point:
    def __init__(self, x, y) -> None:
        self.x = x
        self.y = y

    def __repr__(self):
        return f"Point({self.x}, {self.y})"

    def __add__(self, other):
        return Point(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        return Point(self.x - other.x, self.y - other.y)

    def __mul__(self, scalar):
        return Point(self.x * scalar, self.y * scalar)

    def __truediv__(self, scalar):
        if scalar == 0:
            raise ValueError("Division by zero")
        return Point(self.x / scalar, self.y / scalar)

    def scalar_product(self, other):
        return self.x * other.x + self.y * other.y

    def cross_product(self, other):
        return self.x * other.y - self.y * other.x

    def distance(self, other):
        return sqrt((self.x - other.x) ** 2 + (self.y - other.y) ** 2)

    def length(self):
        return sqrt(self.x**2 + self.y**2)

    def angle(self, other):
        len_self = self.length()
        len_other = other.length()
        if len_self == 0 or len_other == 0:
            raise ValueError("Cannot compute angle with zero-length vector")
        return acos(self.scalar_product(other) / (len_self * len_other))


def calc_area(sholace):
    two_a = sholace[0][-1] * sholace[1][0] - sholace[0][0] * sholace[1][-1]
    for i in range(0, len(sholace[0]) - 1):
        two_a += sholace[0][i] * sholace[1][i + 1] - sholace[0][i + 1] * sholace[1][i]

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
