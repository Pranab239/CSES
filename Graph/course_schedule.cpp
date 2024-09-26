#include<bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	int m; cin >> m;
	vector<int> adjList[n+1];
	for(int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adjList[u].push_back(v);
	}

	// Kahn's algorithm for topoSort
	vector<int> inDeg(n+1, 0);
	for(int i = 1; i <= n; i++) {
		for(int adjNode : adjList[i]) {
			inDeg[adjNode]++;
		}
	}

	queue<int> q;
	vector<int> ans;
	for(int i = 1; i <= n; i++) {
		if(inDeg[i] == 0) {
			q.push(i);
		}
	}

	while(!q.empty()) {
		int node = q.front();
		q.pop();

		ans.push_back(node);

		for(int adjNode : adjList[node]) {
			inDeg[adjNode]--;
			if(inDeg[adjNode] == 0) q.push(adjNode);
		}
	}

	if(ans.size() != n) {
		cout << "IMPOSSIBLE";
		return 0;
	}
	for(int num : ans) cout << num << " ";
	return 0;
}