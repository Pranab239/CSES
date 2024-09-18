#include<bits/stdc++.h>
using namespace std;

// Dijkstra with state for each node, one node is for coupon used and another is used for coupon 
// not used. Ultimately return the distance of the last node's coupon used value.
int main() {
	int n; cin >> n;
	int m; cin >> m;
	vector<vector<int>> edges(m, vector<int>(3));
	vector<pair<int,int>> adjList[n+1];
	map<pair<int,int>, int> weight;
	for(int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adjList[u].push_back({v,w});
		weight[{u,v}] = w;
	}


	// Dijkstra's Algorithm: pair<long long, pair<int,bool>> <dist,{node, coupon}>
	vector<vector<long long>> dist(n+1, vector<long long>(2, 1e15));	// First: false Coupon Second: True Coupon
	priority_queue<pair<long long, pair<int,bool>>, vector<pair<long long, pair<int,bool>>>, greater<pair<long long, pair<int,bool>>>> minH;
	minH.push({0,{1,false}});
	dist[1] = {0,0};

	while(!minH.empty()) {
		long long dst = minH.top().first;
		int node = minH.top().second.first;
		bool coupon = minH.top().second.second;
		minH.pop();

		if(dst > dist[node][coupon]) continue;

		for(auto it : adjList[node]) {
			int adjNode = it.first;
			int edW = it.second;

			if(coupon == false) {
				int newDist = edW / 2;
				if(dst + newDist < dist[adjNode][true]) {
					dist[adjNode][true] = dst + newDist;
					minH.push({dst + newDist, {adjNode, true}});
				}
				if(dst + edW < dist[adjNode][false]) {
					dist[adjNode][false] = dst + edW;
					minH.push({dst + edW, {adjNode, false}});
				}
			}
			else {
				if(dst + edW < dist[adjNode][true]) {
					dist[adjNode][true] = dst + edW;
					minH.push({dst + edW, {adjNode, true}});
				}
			}
		}
	}

	cout << dist[n][1];
}