#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int maxScheduledActivities(int n, int k, vector<pair<int, int>>& activities) {
    sort(activities.begin(), activities.end());

    priority_queue<int, vector<int>, greater<int>> classrooms;

    int count = 0;

    for (auto& activity : activities) {
        int start = activity.first;
        int end = activity.second;

        if (!classrooms.empty() && classrooms.top() < start) {
            classrooms.pop(); 
        }
        
        if (classrooms.size() < k) {
            classrooms.push(end);
            count++;
        }
    }

    return count;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<pair<int, int>> activities(n);
    for (int i = 0; i < n; i++) {
        cin >> activities[i].first >> activities[i].second;
    }

    cout << maxScheduledActivities(n, k, activities) << endl;
    return 0;
}
