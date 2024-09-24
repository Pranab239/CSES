#include<bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	int m; cin >> m;
	int k; cin >> k;
	vector<pair<int,int>> adjList[n+1];
	for(int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adjList[u].push_back({v,w});
	}

	vector<int> ans;
	vector<vector<long long>> dist(n+1, vector<long long>(k, 1e15));
	priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> minH;
	minH.push({0,1});
	dist[1][0] = 0;

	while(!minH.empty()) {
		int node = minH.top().second;
		long long dst = minH.top().first;
		minH.pop();

		if(dist[node][k-1] < dst) continue;

		for(auto it : adjList[node]) {
			int adjNode = it.first;
			int edW = it.second;

			if(dist[adjNode][k-1] > dst + edW) {
				dist[adjNode][k-1] = dst + edW;
				minH.push({dst + edW, adjNode});
				sort(dist[adjNode].begin(), dist[adjNode].end());	// Main trick
			}
		}
	}

	for(auto w : dist[n]) cout << w << " ";
	return 0;
}