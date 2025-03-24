#include <iostream>
#include <unordered_map>
#include <deque>
#include <algorithm>
#include <iterator>
#include <set>
#include <vector>
#include <sstream>
#include <queue>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    cin >> n;
    int node;
    unordered_map<int, int> nodes;
    deque<int> order;

    int largest{0};
    while(n > 0) {
        cin >> node;
        if (node > largest) {
            largest = node;
        }
        nodes[node]++;
        order.push_back(node);
        n--;
    }

    // set<int> leafs;
    priority_queue<int, vector<int>, greater<int>> leafs;
    for(int i{1}; i<=largest; i++) {
        if (nodes.find(i) == nodes.end()) {
            leafs.push(i);
        }   
    }
    
    vector<int> edges;
    // std::cout << order.size() << std::endl;
    if (leafs.size() == 0) {
        std::cout << "Error" << std::endl;
        return 0;
    }

    while(!order.empty() && !leafs.empty()) {
        node = order.front();
        order.pop_front();
        nodes[node]--;
        edges.push_back(leafs.top());
        leafs.pop();

        if (nodes[node]==0) { //No more connections, it is a leaf
            leafs.push(node);   
        }
    }

    if (order.empty() && !leafs.empty()) {
        std::ostringstream buffer;
        for (int num : edges) {
            buffer << num << "\n";  // Store in buffer
        }
        std::cout << buffer.str();  // Flush buffer all at once
    } else {
        std::cout << "Error" << std::endl;
    }
    
}