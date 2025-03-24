/*
    Gustav Carlsson (gusca083)
    time-complexty O(nlog(n)) 
    This is due to the sort which is nlog(n), 
    whilst the while loop is just O(n), since it only runs through the list once even in worst case.
    Idea is to sort the different intervals and then pick the one that streaches furthest to the 
    right of the possible selections. Then continue from the last one
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iterator>
#include <climits>

using namespace std;

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

bool find_smallest_covering(vector<int>& indexes, double left_bound, double right_bound, vector<pair<double, double>>& intervals, int n) {
    double max_right;
    int max_index;
    int previous = 0;

    while (left_bound < right_bound) {
        max_right = left_bound;
        max_index = -1;

        for (int i{previous}; i < n; i++) {
            // Find the one that streaches longest to the left
            // Since intervals is sorted this is makes sure that no intervals are rechecked
            if (intervals[i].first <= left_bound && max_right <= intervals[i].second) { 
                max_right = intervals[i].second;
                max_index = i;
            }
            //Store the last one possible, since we don't need to recheck them the next iteration
            if (intervals[i].first <= left_bound) {
                previous = i;
            }
        }

        if (max_index == -1) { //None found, impossible
            return false;
        }

        indexes.push_back(max_index);
        left_bound = max_right; 
        ++previous;

        if (right_bound <= left_bound) {
            return true;
            // break;
        }
    }
    return false;
}

int main() {
    double left_bound, right_bound;
    while (cin >> left_bound >> right_bound) {
        int n;
        cin >> n;
        vector<pair<double, double>> intervals;
        //Use map for faster reconstruction of final indexes after sorting
        std::unordered_map<std::pair<double, double>, int, pair_hash> original_indexes;
        double lhs, rhs;
        bool found = false;
        for (int i = 0; i < n; i++) {
            cin >> lhs >> rhs;
            auto el = make_pair(lhs, rhs);
            intervals.push_back(el);
            original_indexes[el] = i;
            if (lhs <= left_bound && right_bound <= rhs && !found) {
                found = true;
                cout << 1 << endl << intervals.size()-1 << endl;
            }
        }

        if (found) { //single interval found, this will always be best
            continue;
        } 
        
        sort(intervals.begin(), intervals.end(), [](auto lh, auto rh) {
            if (lh.first != rh.first) {
                return lh.first < rh.first;
            } else {
                return lh.second < rh.second;
            }
        });
        vector<int> indexes;
        found = find_smallest_covering(indexes, left_bound, right_bound, intervals, n);

        // If solution is found, print the results
        if (found) {
            vector<int> indices;
            cout << indexes.size() << "\n";
            for (const auto& p : indexes) {
                indices.push_back(original_indexes[intervals[p]]);
            }
            copy(indices.begin(), indices.end(), ostream_iterator<int>{cout, " "});
            std::cout << endl;
        } else {
            cout << "impossible" << endl;
        }
    }
}
