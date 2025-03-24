#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

int largest_perfect_pth_power(double value) {
    int p = 1; 
    double root = 0;
    int best = 1;
    double isNegative{false};
    if (value < 0) {
        value = -value;
        isNegative=true;
    }

    while (pow(value, 1.0/p) >= 2) { 
        root = pow(value, 1.0 / p);  
        // std::cout << "Val: " << value << ", p: " << p << ", root: " << pow(value, 1.0 / p) << std::endl;
        // std::cout << "Trunc: " << fabs(root - std::round(root)) << std::endl;
        if (fabs(root - std::round(root)) < 1e-9) { 
            // std::cout << "Got here with p: " << p << std::endl;
            best = p;  
        }
        ++p;
    }

    if (isNegative && best%2==0) { //negative, can't be even
        while(best%2==0) {
            best = best / 2;
        }
    }
    return best;
}

int main() {
    while(true) {
        int value;
        cin >> value;
        if(value==0) {
            break;
        } else {
            std::cout << largest_perfect_pth_power(value) << std::endl;
        }
    }
}