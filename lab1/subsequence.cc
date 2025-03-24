/*
    Gustav Carlsson (gusca083)
    
    Find the longest subsequence of elements in an array
    Time complexity: O(nlog(n))
*/
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    long n;
    while (cin >> n) {
        vector<long> nums(n);
        for (long i = 0; i < n; i++) {
            cin >> nums[i];
        }
        
        /*
        Keep track with d of which elements a subsequence of length l ends, ie d[l] contains the end
        of the sequence of length l. The other two are used to keep track of their parent and their index in nums
        so it's easy to reconstruct.
        */
        vector<long> d(n + 1, LONG_MAX);
        vector<long> indices(n + 1, -1);
        vector<long> parent(n, -1); 
        d[0] = LONG_MIN;

        for (int i = 0; i < n; i++) {
            size_t l = upper_bound(d.begin(), d.end(), nums[i]) - d.begin();
            if (d[l - 1] < nums[i] && nums[i] < d[l]) {
                d[l] = nums[i];
                indices[l] = i;
                parent[i] = indices[l - 1];
            }
        }

        long longest = -1;
        long end_index = -1;
        for (int l = 0; l <= n; l++) {
            if (d[l] < LONG_MAX) {
                longest = l;
                end_index = indices[l];
            }
        }

        vector<long> seq;
        for (long i = end_index; i != -1; i = parent[i]) {
            seq.push_back(i);
        }

        // Elements are added from end to begining
        reverse(seq.begin(), seq.end());

        cout << seq.size() << endl;
        for (long index : seq) {
            cout << index << " ";
        }
        cout << endl;
    }

    return 0;
}
