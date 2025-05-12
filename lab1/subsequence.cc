/*
    Gustav Carlsson (gusca083)

    Find the longest subsequence of elements in an array
    Time complexity: O(nlog(n))
*/
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;


vector<size_t> find_longest_increasing_subsequence(const vector<long> &nums) {
  if (nums.empty())
    return {};

  vector<long> d(nums.size() + 1, LONG_MAX);
  vector<size_t> indices(nums.size() + 1, -1);
  vector<size_t> parent(nums.size(), -1);
  d[0] = LONG_MIN;
  /*
          Keep track with d of which elements a subsequence of length l ends, ie
     d[l] contains the end of the sequence of length l. The other two are used
     to keep track of their parent and their index in nums so it's easy to
     reconstruct.
          */
  for (size_t i = 0; i < nums.size(); i++) {
    size_t l = upper_bound(d.begin(), d.end(), nums[i]) - d.begin();
    if (d[l - 1] < nums[i] && nums[i] < d[l]) {
      d[l] = nums[i];
      indices[l] = i;
      parent[i] = indices[l - 1];
    }
  }

  size_t longest = 0;
  size_t end_index = 0;
  for (size_t l = 0; l <= nums.size(); l++) {
    if (d[l] < LONG_MAX) {
      longest = l;
      end_index = indices[l];
    }
  }

  vector<size_t> seq;
  for (size_t i = end_index; i != -1; i = parent[i]) {
    seq.push_back(i);
  }
  reverse(seq.begin(), seq.end());

  return seq;
}

int main() {
  long n;
  while (cin >> n) {
    vector<long> nums(n);
    for (long i = 0; i < n; i++) {
      cin >> nums[i];
    }

    auto lis_indices = find_longest_increasing_subsequence(nums);

    cout << lis_indices.size() << endl;
    for (auto index : lis_indices) {
      cout << index << " ";
    }
    cout << endl;
  }
  return 0;
}
