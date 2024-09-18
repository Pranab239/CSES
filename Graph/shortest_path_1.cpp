#include<bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	int m; cin >> m;
	vector<vector<int>> routes(m, vector<int>(3));
	for(int i = 0; i < m; i++) {
		cin >> routes[i][0];
		cin >> routes[i][1];
		cin >> routes[i][2];
	}

	vector<long long> dist(n+1, 1e15);
	vector<pair<int,int>> adjList[n+1];
	for(auto vec : routes) {
		adjList[vec[0]].push_back({vec[1],vec[2]});
	}

	// Dijkstra's Algorithm
	priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> minH;
	minH.push({0,1});
	dist[1] = 0;

	while(!minH.empty()) {
		long long ew = minH.top().first;
		int node = minH.top().second;
		minH.pop();

		// If we get a node which is already been reached with a shorter dist than current dist
		// then we don't consider the node again, as we have a better option before.
		if(ew > dist[node]) continue;

		for(auto it : adjList[node]) {
			int adjNode = it.first;
			int edW = it.second;

			if(ew + edW < dist[adjNode]) {
				dist[adjNode] = ew + edW;
				minH.push({edW+ew, adjNode});
			}
		}
	}

	for(int i = 1; i < n+1; i++) cout << dist[i] << " ";	
	return 0;
}