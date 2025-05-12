/*
 * Gustav Carlsson (gusca083)
 * Problem description: Find all occurrences of a substring (pattern) in a given string (text)
 * Time complexity: O(n + m), where n = length of text and m = length of pattern
 * Memory complexity: O(n + m)
 * Expects an even number of input lines (alternating pattern and text)
 * Uses the Knuth-Morris-Pratt algorithm
 * The algorithm preprocesses the pattern to build an LPS (Longest Prefix Suffix) array,
 * which is then used to efficiently search the pattern in the text.
 * When a mismatch occurs, the LPS array determines how far to skip ahead in the pattern,
 * this makes the algorithm be in linear time. 
 */                                                                                                                    \
#include<iostream>
#include <string>
#include <vector>

using namespace std;

vector<size_t> compute_lps(const string &pattern)
{
    size_t m = pattern.size();
    vector<size_t> lps(m, 0);
    size_t len = 0;

    for (size_t i = 1; i < m;)
    {
        if (pattern[i] == pattern[len])
        {
            lps[i++] = ++len;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i++] = 0;
            }
        }
    }
    return lps;
}

vector<size_t> find_matching(const string &pattern, const string &text)
{
    vector<size_t> found;
    size_t m = pattern.size(), n = text.size();
    if (m > n)
        return found;

    vector<size_t> lps = compute_lps(pattern);
    size_t i = 0, j = 0;

    while (i < n)
    {
        if (pattern[j] == text[i])
        {
            i++;
            j++;
        }
        if (j == m)
        {
            found.push_back(i - j);
            j = lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    return found;
}

int main()
{
    string pattern, text;
    while (getline(cin, pattern) && getline(cin, text))
    {
        auto matching = find_matching(pattern, text);
        for (size_t i = 0; i < matching.size(); ++i)
        {
            if (i > 0)
                cout << " ";
            cout << matching[i];
        }
        cout << endl;
    }
}
