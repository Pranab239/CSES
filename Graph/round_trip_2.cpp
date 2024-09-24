#include<bits/stdc++.h>
using namespace std;

bool DFS(int node, vector<bool>& vis, vector<bool>& inRec, vector<int>& parent, vector<int> adjList[], int& cycleNode) {
	vis[node] = true;
	inRec[node] = true;

	for(int adjNode : adjList[node]) {
		if(!vis[adjNode]) {
			parent[adjNode] = node;
			if(DFS(adjNode, vis, inRec, parent, adjList, cycleNode) == true) return true;
			parent[adjNode] = -1;
		}
		if(inRec[adjNode]) {
			cycleNode = adjNode;
			parent[adjNode] = node;
			return true;
		}
	}

	inRec[node] = false;
	return false;
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

	vector<bool> vis(n+1, false);
	vector<bool> inRec(n+1, false);
	vector<int> parent(n+1, -1);
	int cycleNode = -1;
	for(int i = 1; i <= n; i++) {
		if(!vis[i]) {
			if(DFS(i, vis, inRec, parent, adjList, cycleNode) == true) break;
		}
	}

	if(cycleNode == -1) {
		cout << "IMPOSSIBLE";
		return 0;
	}

	// cout << cycleNode << endl;
	// for(int num : parent) cout << num << " ";

	vector<int> cycle;
	cycle.push_back(cycleNode);
	int node = parent[cycleNode];
	while(node != cycleNode) {
		cycle.push_back(node);
		node = parent[node];
	}
	cycle.push_back(cycleNode);
	reverse(cycle.begin(), cycle.end());
	cout << cycle.size() << endl;
	for(int num : cycle) cout << num << " ";
	return 0;
}