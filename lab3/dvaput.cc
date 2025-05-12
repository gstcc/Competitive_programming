/*
 * Gustav Carlsson (gusca083)
 * Time complexity O(nlog(n))
 * Memory complexity O(n)
 * Finds the longest substring appearing twice in a given string
 *
 *
 * This is done by taking the suffix of each position and then sorting them based on their
 * lexographical order. * At each iteration, the suffixes are compared using the first 2ᵏ characters.
 * If a suffix is shorter than that, -1 is returned as a placeholder,
 * indicating that the suffix has reached the end.
 * The vector that is returned from build_suffix_array contains
 * the starting positions of these sorted suffixes.
 * The LCP array is built by comparing each suffix with the previous one in the sorted order.
 * We don't need to compare with other since the suffix array is sorted in lexographicall order:
 * For each pair of consecutive suffixes, we find how many characters they share in common from the start.
 * If a suffix is shorter than the other, we stop the comparison and move to the next pair.
 * The length of the overlap is stored in the array, and the highest value in the LCP array is the length of the longest repeated substring.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> build_suffix_array(const string &s)
{
    int n = s.size();
    vector<int> sa(n), rank(n), temp(n);

    for (int i = 0; i < n; ++i)
    {
        sa[i] = i;
        rank[i] = s[i];
    }

    for (int k = 1; k < n; k <<= 1)
    {
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

vector<int> build_lcp_array(const string &s, const vector<int> &sa)
{
    int n = s.size();
    vector<int> rank(n), lcp(n - 1);
    for (int i = 0; i < n; ++i)
        rank[sa[i]] = i;

    int h = 0;
    for (int i = 0; i < n; ++i)
    {
        if (rank[i] > 0)
        {
            int j = sa[rank[i] - 1];
            while (i + h < n && j + h < n && s[i + h] == s[j + h])
                ++h;
            lcp[rank[i] - 1] = h;
            if (h > 0)
                --h;
        }
    }
    return lcp;
}

int main()
{
    int n;
    string s;
    cin >> n >> s;

    vector<int> sa = build_suffix_array(s);
    vector<int> lcp = build_lcp_array(s, sa);

    int max_len = 0;
    for (int len : lcp)
        max_len = max(max_len, len);

    cout << max_len << endl;
}
