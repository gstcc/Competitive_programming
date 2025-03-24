#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
const int MAX_IMPLICATIONS = 50000;
int base[MAX_IMPLICATIONS], discoveryTime[MAX_IMPLICATIONS], lowlink[MAX_IMPLICATIONS];

vector<vector<int>> nodes;
vector<int> edges;
int K = 0, discoveries = 0, outs = 0;

int findScc(int v) {
    base[v] = lowlink[v] = discoveryTime[v] = ++discoveries;
    edges.push_back(v);
    for (auto it = nodes[v].begin(); it != nodes[v].end(); ++it) {
        base[v] = min(base[v], (discoveryTime[*it] ? base[*it] : (base[*it] ? base[v] : findScc(*it))));
    }
    if (lowlink[v] == base[v] && ++K) {
        do {
            lowlink[v] = edges.back();
            edges.pop_back();
            base[lowlink[v]] = v;
            discoveryTime[lowlink[v]] = 0;
        } while (lowlink[v] != v);
    }
    return discoveryTime[v] ? base[v] : (lowlink[v]=0)+discoveries;
}

void scc() {
    int s, I, a, b;
    cin >> s >> I;
    nodes.clear();
    nodes.resize(MAX_IMPLICATIONS);
    for (int i{1}; i<=I; i++) {
        cin >> a >> b;
        nodes[a].push_back(b);
    }
    memset(discoveryTime, 0, sizeof(discoveryTime));
    memset(lowlink, 0, sizeof(lowlink));
    memset(base, 0, sizeof(base));
    K = discoveries = outs = 0;
    for (int i{1}; i<=s; i++) {
        if (!base[i]) {
            findScc(i);
        }
    }
    discoveries = 0;
    for (int i = 1; i <= s; ++i) {
        for (auto el : nodes[i]) {
            if (base[i] != base[el]) {
                if (!lowlink[base[i]]++) ++outs;
                if (!discoveryTime[base[el]]++) ++discoveries;
            }
        } 
    }
    
  cout << (K > 1 ? max(K-discoveries, K-outs) : 0) << endl;;

}


int main() {
    int n;
    cin >> n;
    for (; n>0; n--) {
        scc();
    }
}