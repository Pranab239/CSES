#include<bits/stdc++.h>
using namespace std;

bool BFS(int cycleNode, int n, vector<int>adjList[], vector<bool>& vis) {
	queue<int> q;
	q.push(cycleNode);
	vis[cycleNode] = true;
	
	while(!q.empty()) {
		int node = q.front();
		q.pop();

		if(node == n) {
			return true;
		}

		for(int adjNode : adjList[node]) {
			if(!vis[adjNode]) {
				vis[adjNode] = true;
				q.push(adjNode);
			}
		}
	}
	return false;
}

int main() {
	int n; cin >> n;
	int m; cin >> m;
	vector<long long> dist(n+1, -1e15);
	vector<vector<int>> edges(m, vector<int>(3));
	for(int i = 0; i < m; i++) {
		cin >> edges[i][0];
		cin >> edges[i][1];
		cin >> edges[i][2];
	}
	vector<int> adjList[n+1];
	vector<bool> vis(n+1, false);
	for(auto vec : edges) {
		adjList[vec[0]].push_back(vec[1]);
	}

	// Bellman ford algorithm but here we need the largest path
	dist[1] = 0;
	for(int i = 0; i < n-1; i++) {
		for(auto it : edges) {
			int u = it[0];
			int v = it[1];
			int wt = it[2];

			// relaxation of edges
			if(dist[u] != -1e15 && dist[u] + wt > dist[v]) {
				dist[v] = dist[u] + wt;
			}
		}
	}

	for(auto it : edges) {
		int u = it[0];
		int v = it[1];
		int wt = it[2];	

		// relaxation of edges
		if(dist[u] != -1e15 && dist[u] + wt > dist[v]) {
			// Now find if there is a path from the cycle to the endNode if possible then return -1
			// otherwise return the dist of endNode.
			if(BFS(u, n, adjList, vis) == true) {
				cout << -1;
				return 0;
			}
		}
	}

	cout << dist[n];
}