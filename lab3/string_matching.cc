/*
* Gustav Carlsson (gusca083)
* Problem description: Find a substring in a given string
* Time-complexity: O(n*m), where m = pattern size and n=string size
* Memory complexity: O(n)
* Expects a even number of strings
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Find each matching pattern in string s, returns a sorted vector, containing the start
// indexes of each substring that matches the pattern
vector<size_t> find_matching(const string& pattern, const string& s) {
    vector<size_t> found;
    size_t m = pattern.size(), n = s.size();
    if (m > n) return found;

    for (size_t i = 0; i <= n - m; ++i) {
        if (s.compare(i, m, pattern) == 0) {
            found.push_back(i);
        }
    }
    return found;
}

int main() {
    string pattern, s;
    while (getline(cin, pattern) && getline(cin, s)) {
        auto matching = find_matching(pattern, s);
        for (size_t i = 0; i < matching.size(); ++i) {
            if (i > 0) cout << " ";
            cout << matching[i];
        }
        cout << endl;
    }
}

