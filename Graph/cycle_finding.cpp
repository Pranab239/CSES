#include<bits/stdc++.h>
using namespace std;

// Idea: Use Bellman Ford Algorithm to find negative cycle, if exist then find the cycle
// using BFS traversal.

void DFS(int node, vector<bool>& vis, vector<int> adjList[]) {
	vis[node] = true;
	for(auto adjNode : adjList[node]) {
		if(!vis[adjNode]) {
			DFS(adjNode, vis, adjList);
		}
	}
}

vector<int> findComponents(int n, int m, vector<vector<int>>& edges) {
	vector<int> adjList[n+1];
	for(auto vec : edges) {
		adjList[vec[0]].push_back(vec[1]);
	}

	vector<bool> vis(n+1, false);
	vector<int> components;
	for(int i = 1; i <= n; i++) {
		if(!vis[i]) {
			components.push_back(i);
			DFS(i, vis, adjList);
		}
	}

	return components;
}

int main() {
	int n; cin >> n;
	int m; cin >> m;

	vector<vector<int>> edges(m, vector<int>(3));
	vector<long long> dist(n+1, 1e15);
	vector<int> parent(n+1, -1);
	for(int i = 0; i < m; i++) {
		cin >> edges[i][0];
		cin >> edges[i][1];
		cin >> edges[i][2];
	}

	vector<int> components = findComponents(n, m, edges);
	// for(int num : components) cout << num << " ";

	// Bellman Ford Algorithm
	for(int num : components) dist[num] = 0;
	for(int i = 0; i < n-1; i++) {
		for(auto vec : edges) {
			int u = vec[0];
			int v = vec[1];
			int w = vec[2];

			if(dist[u] != 1e15 && dist[u] + w < dist[v]) {
				parent[v] = u;
				dist[v] = dist[u] + w;
			}
		}
	}

	// check for one more time if negative cycle present or not
	int cycleNode = -1;
	for(auto vec : edges) {
		int u = vec[0];
		int v = vec[1];
		int w = vec[2];

		if(dist[u] != 1e15 && dist[u] + w < dist[v]) {
			cycleNode = u;
			parent[v] = u;
		}
	}

	if(cycleNode == -1) {
		cout << "NO";
		return 0;
	}
	cout << "YES" << endl;
	// cout << cycleNode << endl;
	// for(int num : parent) cout << num << " ";
	// cout << endl;

	vector<int> path;
	unordered_set<int> nodes;
	int ind = cycleNode;

	while(nodes.find(ind) == nodes.end()) {
		// cout << ind << " " << parent[ind] << endl;
		nodes.insert(ind);
		path.push_back(ind);
		ind = parent[ind];
	}

	path.push_back(ind);
	auto cycleStart = find(path.begin(), path.end(), ind);
	path.erase(path.begin(), cycleStart);
	reverse(path.begin(), path.end());
	for(int num : path) cout << num << " ";
}