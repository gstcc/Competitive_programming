#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;


int min_swaps(string s) {
    int left = 0;
    int right = s.size() - 1;
    int swaps = 0;

    while (left < right) {
        if (s[left] == s[right]) {
            left++;
            right--;
        } else {
            int match = right;
            while (match > left && s[match] != s[left]) {
                match--;
            }

            if (match == left) {
                // Special case: unmatched char on left side — bubble it toward center
                swap(s[match], s[match + 1]);
                swaps++;
            } else {
                // Bring s[match] to s[right] by adjacent swaps
                while (match < right) {
                    swap(s[match], s[match + 1]);
                    swaps++;
                    match++;
                }
                left++;
                right--;
            }
        }
    }
    return swaps;
}


int main() {
	int T;
	cin >> T;
	while(T--) {
		string s;
		cin >> s;
		unordered_map<char, int> occ;
		for(char c : s) {
			++occ[c];
		}
		int uneven_count = 0;
		for (auto [_, c] : occ) {
			if (c % 2 == 1) uneven_count++;
		}
		if ((uneven_count != 1 && s.size() % 2 == 1) || (uneven_count != 0 && s.size() % 2 == 0 )) {
			cout << "Impossible" << endl;
			continue;
		}
	
		std::cout << min_swaps(s) << std::endl;
	}
}
