#include<bits/stdc++.h>
using namespace std;

void DFS(int node, vector<int> adjList[], vector<bool>& vis, stack<int>& st) {
	vis[node] = true;
	for(int adjNode : adjList[node]) {
		if(!vis[adjNode]) {
			DFS(adjNode, adjList, vis, st);
		}
	}
	st.push(node);
}

int main() {
	int n; cin >> n;
	int m; cin >> m;
	vector<int> adjList[n+1];
	for(int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adjList[u].push_back(v);
	}

	vector<int> parent(n+1, -1);
	vector<int> dist(n+1, INT_MIN);
	vector<bool> visited(n+1, false);
	stack<int> st;
	parent[1] = 1;
	dist[1] = 0;

	DFS(1, adjList, visited, st);

	while(!st.empty()) {
		int node = st.top();
		st.pop();

		for(int adjNode : adjList[node]) {
			if(dist[adjNode] < dist[node] + 1) {
				dist[adjNode] = dist[node] + 1;
				parent[adjNode] = node;
			}
		}
	}

	// for(int num : dist) cout << num << " ";
	// cout << endl;
	
	if(dist[n] == INT_MIN) {
		cout << "IMPOSSIBLE";
		return 0;
	}

	vector<int> path;
	int node = n;
	while(node != parent[node]) {
		path.push_back(node);
		node = parent[node];
	}
	path.push_back(node);
	reverse(path.begin(), path.end());

	cout << path.size() << endl;
	for(int num : path) cout << num << " ";

	return 0;
}