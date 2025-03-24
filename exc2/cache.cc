#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int main() {
    int c, n, m;  // c = cache capacity, n = number of objects, m = number of accesses
    cin >> c >> n >> m;
    if (c==0) {
        std::cout << 0 << std::endl; //No cache, nothing to read into
        return 1;
    }
    unordered_map<int, int> usages_left;

    vector<int> accesses(m);
    int tmp;
    for (int i = 0; i < m; i++) {
        cin >> tmp;
        accesses[i] = tmp;
        usages_left[tmp]++;
    }

    unordered_map<int, int> cache;  
    int cacheMisses = 0;

    for (int i = 0; i < m; i++) {
        int currentAccess = accesses[i];
        if (cache.contains(currentAccess)) {
            usages_left[currentAccess] -= 1;
            continue;
        }

        if (cache.size()==c) {
            int furthestElement = -1;
            bool found{false};
            for (auto&& [key, value] : cache) {
                if (usages_left[key] == 0) {
                    furthestElement = key;
                    found = true;
                    break;
                }
            }

            if (!found) {
                //all elements are in cache are left remove the furthest one
                unordered_map<int, int> found_elems;
                for (int j = i+1; j < m; j++) {
                    if (!found_elems.contains(accesses[j])){
                        furthestElement = accesses[j];
                        found_elems[accesses[j]] = j;
                    }
                }
            }
            cache.erase(furthestElement);   
        }

        cache[currentAccess] = 1;
        ++cacheMisses;        
    }

    cout << cacheMisses << endl;

    return 0;
}
