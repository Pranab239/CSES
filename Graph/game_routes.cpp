#include<bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	int m; cin >> m;
	int MOD = 1e9 + 7;
	vector<int> adjList[n+1];
	for(int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adjList[u].push_back(v);
	}

	// First do a topoSort to eliminate the extra 0 indegree edges other than 1
	vector<int> inDeg(n+1, 0);
	for(int i = 1; i <= n; i++) {
		for(int adjNode : adjList[i]) {
			inDeg[adjNode]++;
		}
	}

	queue<int> q;
	for(int i = 2; i <= n; i++) {
		if(inDeg[i] == 0) q.push(i);
	}

	while(!q.empty()) {
		int node = q.front();
		q.pop();

		for(int adjNode : adjList[node]) {
			inDeg[adjNode]--;
			if(adjNode != 1 && inDeg[adjNode] == 0) {
				q.push(adjNode);
			}
		}
	}
	// for(int i = 1; i <= n; i++) cout << inDeg[i] << " ";
	// cout << endl;

	// Now again do a topoSort to count the number of topoSort from node 1
	vector<long long> cnt(n+1, 0);
	cnt[1] = 1;

	q.push(1);
	while(!q.empty()) {
		int node = q.front();
		q.pop();

		for(int adjNode : adjList[node]) {
			inDeg[adjNode]--;
			cnt[adjNode] = (cnt[adjNode] + cnt[node]) % MOD;
			if(inDeg[adjNode] == 0) {
				q.push(adjNode);
			}
		}
	}
	// for(int i = 1; i <= n; i++) cout << cnt[i] << " ";
	// cout << endl;
	cout << cnt[n];

	return 0;
}