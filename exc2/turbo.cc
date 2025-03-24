#include <iostream>
#include <vector>
using namespace std;

//basically a fenwick tree
class IndToVal {
public:
    IndToVal(int n) : tree(n + 1, 0) {}

    void add(int index, int value) {
        index++;
        while (index < tree.size()) {
            tree[index] += value;
            index += index & -index;
        }
    }

    int sum(int index) {
        index++; 
        int result = 0;
        while (index > 0) {
            result += tree[index];
            index -= index & -index; //parent
        }
        return result;
    }

    int sum(int left, int right) {
        return sum(right) - sum(left - 1);
    }

private:
    vector<int> tree;
};

void solve(vector<int>& array, vector<int>& indexes, IndToVal& indVal) {
    int n = array.size();
    int startIndex = 0;
    int endIndex = n - 1;
    bool isStart = true;

    while (startIndex != endIndex) {
        if (isStart) {
            int index = indexes[startIndex];
            indVal.add(index, -1);
            int swaps = indVal.sum(index);
            cout << swaps << std::endl;
            startIndex++;
        } else {
            int index = indexes[endIndex];
            indVal.add(index, -1);
            int swaps = indVal.sum(index, n - 1);
            cout << swaps << std::endl;
            endIndex--;
        }
        isStart = !isStart;
    }

    cout << std::endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> array(n);
    vector<int> indexes(n);
    IndToVal indVal(n);

    for (int i = 0; i < n; ++i) {
        int number;
        cin >> number;
        number--; // Convert to 0-based index
        array[i] = number;
        indexes[number] = i;
        indVal.add(i, 1);
    }

    solve(array, indexes, indVal);

    return 0;
}
