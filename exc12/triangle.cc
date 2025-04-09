#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

bool areColinear(int x1, int y1, int x2, int y2, int x3, int y3) {
    return (y2-y1)*(x3-x2)==(y3-y2)*(x2-x1);
}

int squaredDistance(int x1, int y1, int x2, int y2) {
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

pair<string, string> classifyTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    // Check for validity
    // Compute squared side lengths
    int ab = squaredDistance(x1, y1, x2, y2);
    int bc = squaredDistance(x2, y2, x3, y3);
    int ca = squaredDistance(x3, y3, x1, y1);

    // Sort sides to simplify angle classification
    int a = ab, b = bc, c = ca;
    if (a > b) swap(a, b);
    if (b > c) swap(b, c);
    if (a > b) swap(a, b);
    // Now: a ≤ b ≤ c

    // Angle classification
    string angleType;
    if (a + b == c)
        angleType = "right";
    else if (a + b < c)
        angleType = "obtuse";
    else
        angleType = "acute";

    // Side classification
    string sideType;
    if (a != b && b != c && a != c)
        sideType = "scalene";
    else
        sideType = "isosceles";
    return {sideType, angleType};
}



int main() {
    int x1, y1, x2, y2, x3, y3;
    int count = 1;
    cin >> x1; //just dummy
    while (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3) {
        if (areColinear(x1, y1, x2, y2, x3, y3)) {
            std::cout << "Case: #" << count << ": not a triangle" << endl; 
        } else if ((x1==x2 && y1==y2) || (x1==x3&&y1==y3) || (x2==x3 && y2==y3)) {
            std::cout << "Case: #" << count << ": not a triangle" << endl; 
        } else {
            auto res = classifyTriangle(x1, y1, x2, y2, x3, y3);
            std::cout << "Case: #" << count << ": " << res.first << " " << res.second << " triangle" << endl; 
        }
        ++count;
    }
    return 0;
}

