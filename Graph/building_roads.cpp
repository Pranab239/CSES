#include<bits/stdc++.h>
using namespace std;

void DFS(int node, vector<bool>& vis, vector<int> adjList[]) {
	vis[node] = true;
	for(auto adjNode : adjList[node]) {
		if(!vis[adjNode]) {
			DFS(adjNode, vis, adjList);
		}
	}
}

int main() {
	int n; cin >> n;
	int m; cin >> m;

	vector<vector<int>> edges(m, vector<int>(2));
	for(int i = 0; i < m; i++) {
		cin >> edges[i][0];
		cin >> edges[i][1];
	}

	vector<int> adjList[n+1];
	for(int i = 0; i < m; i++) {
		adjList[edges[i][0]].push_back(edges[i][1]);
		adjList[edges[i][1]].push_back(edges[i][0]);
	}

	vector<bool> vis(n+1, false);
	int components = 0;
	vector<int> parents;

	for(int i = 1; i <= n; i++) {
		if(!vis[i]) {
			parents.push_back(i);
			components++;
			DFS(i, vis, adjList);
		}
	}
	
	int size = parents.size();
	cout << components - 1 << endl;
	for(int i = 0; i < size - 1; i++) {
		cout << parents[i] << " " << parents[i+1] << endl;
	}
}
