// Author: Adrian Kuegel
// Date: September 8th, 2010
// Algorithm: binary search + network flow
// Complexity: O(n^3 log m)

#include <queue>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <limits.h>
using namespace std;

#define MAXN 100
#define MAXV (MAXN*2+2)

typedef vector<int> VI;
typedef queue<int> QI;
typedef pair<int, int> PII;
typedef vector<PII> VPII;

VPII a[MAXV];
VI g[MAXV+1]; // for gap heuristic
int h[MAXV];
int e[MAXV];
int pos[MAXV];
VPII::iterator current[MAXV];
int ecap[2*MAXN*(MAXN-1)+6*MAXN], ecap_save[2*MAXN*(MAXN-1)+6*MAXN];
int m;
QI q;

int Preflow(int n, int src, int sink)
{
	memset(h, 0, sizeof(int) * n);
	memset(e, 0, sizeof(int) * n);
	for (int i=0; i<n; ++i) {
		g[i].clear();
		current[i] = a[i].begin();
		if (i != src && i != sink) {
			pos[i] = g[0].size();
			g[0].push_back(i);
		}
	}
	g[n].clear();
	h[src] = n;
	for (VPII::iterator it=a[src].begin(); it!=a[src].end(); ++it)
		if (ecap[it->second] > 0)
		{
			e[it->first] = ecap[it->second];
			e[src] -= ecap[it->second];
			ecap[(it->second + m) % (2 * m)] += ecap[it->second];
			ecap[it->second] = 0;
			if (it->first != sink)
				q.push(it->first);
		}
	int max_not_empty = 0;
	// for the gap heuristic, we maintain following invariant:
	// g[i] is non-empty for i in [0...max_not_empty]
	// g[i] is empty for i in [max_not_empty + 1...n]
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		while (e[u] > 0)
			if (current[u] == a[u].end())
			{
				// if we are here, it means we skipped through the whole list since the last update of h[u]
				// so there is no v with h[v] + 1 = h[u] and c[u][v] - f[u][v] > 0
				// since we maintain the property h[v] >= h[u]-1 this means in fact h[v] >= h[u]
				int lowest = INT_MAX; //2*n + 1;
				// relabel
				for (VPII::iterator it = a[u].begin(); it != a[u].end(); ++it)
					if (ecap[it->second] > 0)
						lowest = min(lowest, h[it->first]);
				++lowest;
				// now lowest > min_v (h[v]) >= h[u]
				assert(lowest > h[u]);
				int oldh = h[u];
				h[u] = lowest;
				// gap heuristic
				if (oldh <= n) {
					// maintain data structures (in O(1))
					// remove vertex u from height oldh list
					VI::iterator it = g[oldh].begin() + pos[u];
					swap(*it, g[oldh].back());
					pos[*it] = pos[u];
					g[oldh].pop_back();
					// insert it in height lowest list
					if (lowest <= n) {
						// we know the node v for which h[v] = lowest-1 is still in list g[lowest-1]
						// so g[lowest-1] is not empty -> lowest-1 <= max_not_empty -> lowest <= max_not_empty+1
						if (g[lowest].empty()) {
							// this means lowest >= max_not_empty+1, so it must follow:
							// lowest == max_not_empty + 1
							assert(lowest == 1 + max_not_empty);
							++max_not_empty;
						}
						pos[u] = g[lowest].size();
						g[lowest].push_back(u);
					}
					if (oldh && g[oldh].empty()) {
						assert(oldh <= max_not_empty);
						// each element is moved at most once, therefore overall O(n)
						for (int i=oldh+1; i<=max_not_empty; ++i) {
							for (VI::iterator it = g[i].begin(); it!=g[i].end(); ++it) {
								h[*it] = n + 1;
								current[*it] = a[*it].begin();
							}
							g[i].clear();
						}
						// oldh-1 must be 0 or not empty, otherwise we would have emptied g[oldh] already
						max_not_empty = oldh-1;
					}
				}
				current[u] = a[u].begin();
			}
			else
			{
				int v = current[u]->first;
				if (ecap[current[u]->second] > 0 && h[u] == h[v] + 1)
				{
					if (e[v] == 0 && v != src && v != sink)
						q.push(v);
					int d = min(e[u], ecap[current[u]->second]);
					ecap[current[u]->second] -= d;
					ecap[(current[u]->second+m)%(2*m)] += d;
					e[u] -= d;
					e[v] += d;
				}
				else
					++current[u];
			}
	}
	return e[sink];
}


int armies[MAXN];
char border[MAXN][MAXN+1];

int main() {
	int tc, n;
	scanf("%d", &tc);
	assert(tc >= 1 && tc <= 100);
	while(tc--) {
		scanf("%d", &n);
		assert(n >= 1 && n <= MAXN);
		for (int i=0; i<n; ++i)
			scanf("%d", &armies[i]);
		m = 0;
		for (int i=0; i<n; ++i) {
			scanf("%s", border[i]);
			assert(border[i][n] == 0 && border[i][i] == 'N');
			for (int j=0; j<n; ++j) {
				assert(border[i][j] == 'Y' || border[i][j] == 'N');
				if (j < i) {
					assert(border[i][j] == border[j][i]);
					if (border[i][j] == 'Y')
						m += 2;
				}
			}
		}
		m += n * 3;
		int N = n*2 + 2;
		for (int i=0; i<N; ++i)
			a[i].clear();
		int l = 0;
		VI special;
		int sum = 0;
		for (int i=0; i<n; ++i) {
			if (!armies[i])
				continue;
			// edge from source to region
			if (armies[i] > 1) {
				a[0].push_back(PII(i+n+1, l));
				ecap_save[l] = armies[i]-1;
				a[i+n+1].push_back(PII(0, l+m));
				ecap_save[l+m] = 0;
				++l;
			}
			// edge to represent node capacity of region
			sum += armies[i];
			a[i+n+1].push_back(PII(i+1, l));
			ecap_save[l] = armies[i];
			a[i+1].push_back(PII(i+n+1, l+m));
			ecap_save[l+m] = 0;
			++l;
			bool outer = false;
			for (int j=0; j<n; ++j)
				if (border[i][j] == 'Y') {
					if (!armies[j])
						outer = true;
					else {
						// add edge to represent possible movement of armies
						a[i+1].push_back(PII(j+n+1, l));
						ecap_save[l] = armies[i];
						a[j+n+1].push_back(PII(i+1, l+m));
						ecap_save[l+m] = 0;
						++l;
					}
				}
			if (outer) {
				special.push_back(l);
				a[i+n+1].push_back(PII(N-1, l));
				a[N-1].push_back(PII(i+n+1, l+m));
				++l;
			}
		}
		assert(!special.empty() && l <= m);
		int lo = 0, hi = sum / (int)special.size();
		while(lo < hi) {
			int mid = (lo + hi + 1)/2;
			memcpy(ecap, ecap_save, sizeof(int) * m * 2);
			for (VI::iterator it=special.begin(); it!=special.end(); ++it) {
				ecap[*it] = mid;
				ecap[*it + m] = 0;
			}
			if (Preflow(N, 0, N-1) == (int)special.size() * mid)
				lo = mid;
			else
				hi = mid - 1;
		}
		printf("%d\n", lo+1);
	}
	return 0;
}
