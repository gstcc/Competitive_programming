/*
* Note: Using the same function build_suffix_array from problem c in this lab
* Gustav Carlsson (gusca083)
* Time complexity O(nlog(n)), space O(n)
* Builds the suffix array in lexiographically sorted order, then just queries
* the suffix in index q
* Finds the starting position of the qi’th smallest suffix of s
*/
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

auto build_suffix_array(const string& s) {
    int n = s.size();
    vector<int> sa(n), rank(n), temp(n);

    for (int i = 0; i < n; ++i) {
        sa[i] = i;
        rank[i] = s[i];
    }

    for (int k = 1; k < n; k <<= 1) {
        auto cmp = [&](int a, int b) {
            if (rank[a] != rank[b])
                return rank[a] < rank[b];
            int ra = (a + k < n) ? rank[a + k] : -1;
            int rb = (b + k < n) ? rank[b + k] : -1;
            return ra < rb;
        };
        sort(sa.begin(), sa.end(), cmp);

        temp[sa[0]] = 0;
        for (int i = 1; i < n; ++i)
            temp[sa[i]] = temp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        rank = temp;
    }

    return sa;
}

int main() {
    string s, qs;
    while(getline(cin, s) && getline(cin, qs)) {
        istringstream iss(qs);
    
        int q;
        auto suffix_array = build_suffix_array(s);
        iss >> q; //just ignore the n, it's unesecary
        while (iss >> q) {
            cout << suffix_array[q] << " ";
        }
        cout << endl;

    }
}

