#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <string>

using namespace std;


int main() {
    std::map<int, std::string> init_vals = {
        {0, "0"},
        {1, "1"},
        {2, "2"},
        {3, "5"},
        {4, "9"},
        {5, "8"},
        {6, "6"}
    };
    int tmp;
    while(cin >> tmp) {
        double t = tmp;
        string s = init_vals[tmp%7];
        bool done{t < 7};
        t /= 7;
        while(!done) {
            tmp /= 7;
            if (t >= 7) {
                s += init_vals[tmp%7];
            } else {
                s += init_vals[floor(t)];
                done = true;
            }
            t /= 7;
        }
        std::cout << s << std::endl;

    }
}

 