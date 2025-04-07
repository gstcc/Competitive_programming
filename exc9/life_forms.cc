#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Common prefix length between two strings
int common_prefix_length(const string& a, const string& b) {
    int len = 0;
    while (len < a.size() && len < b.size() && a[len] == b[len]) {
        ++len;
    }
    return len;
}

int main() {
    int n;
    bool first_case = true;
    while (cin >> n && n != 0) {
        string dummy;
        getline(cin, dummy); 

        if (!first_case) cout << endl;
        first_case = false;

        vector<string> strings(n);
        for (int i = 0; i < n; ++i)
            getline(cin, strings[i]);

        vector<pair<string, int>> suffixes;

        // Collect all suffixes
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < strings[i].size(); ++j) {
                suffixes.emplace_back(strings[i].substr(j), i);
            }
        }

        sort(suffixes.begin(), suffixes.end());
        int best = 0;
        int k = suffixes.size();

        // First pass
        unordered_map<int, int> count;
        int i = 0, j = 0, distinct = 0;
        while (i < k) {
            while (distinct <= n / 2 && i < k) {
                if (++count[suffixes[i].second] == 1)
                    ++distinct;
                ++i;
            }
            while (distinct > n / 2) {
                if (--count[suffixes[j].second] == 0)
                    --distinct;
                ++j;
            }
            if (j > 0) {
                int lcp = common_prefix_length(suffixes[j - 1].first, suffixes[i - 1].first);
                best = max(best, lcp);
            }
        }

        // Second pass
        if (best == 0) {
            cout << "?" << endl;
        } else {
            string prev = "";
            count.clear();
            i = j = distinct = 0;

            while (i < k) {
                while (distinct <= n / 2 && i < k) {
                    if (++count[suffixes[i].second] == 1)
                        ++distinct;
                    ++i;
                }
                while (distinct > n / 2) {
                    if (--count[suffixes[j].second] == 0)
                        --distinct;
                    ++j;
                }
                if (j > 0) {
                    int lcp = common_prefix_length(suffixes[j - 1].first, suffixes[i - 1].first);
                    if (lcp == best) {
                        string candidate = suffixes[j - 1].first.substr(0, best);
                        if (candidate != prev) {
                            cout << candidate << endl;
                            prev = candidate;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
