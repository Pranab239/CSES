#include<bits/stdc++.h>
using namespace std;

// Do DFS for cycle detection if cycle is present then a round trip is always possible, but we need to
// find any two nodes present in that cycle because there can be an 1 degree node and cycle is formed
// later in the graph, so if the src is that 1 degree node then we will not find any round trip.
bool DFS(int node, vector<int>& parent, vector<bool>& vis, vector<int> adjList[], int& src, int& dst) {
	vis[node] = true;
	for(auto adjNode : adjList[node]) {
		if(!vis[adjNode]) {
			parent[adjNode] = node;
			if(DFS(adjNode, parent, vis, adjList, src, dst) == true) return true;
		}
		// adjNode already visited and not parent hence cycle
		else if(parent[node] != adjNode) {
			src = adjNode;
			dst = node;
			return true;
		}
	}
	return false;
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
	
	vector<int> parent(n+1, -1);
	for(int i = 0; i < n+1; i++) parent[i] = i;
	vector<bool> vis(n+1, false);
	int src = -1;
	int dst = -1;

	for(int i = 1; i <= n; i++) {
		if(!vis[i]) {
			// Cycle exist means path can be formed
			if(DFS(i, parent, vis, adjList, src, dst) == true) {
				int ind = dst;
				vector<int> path;

				// Form the path from the dst to the src and then add the src again
				while(ind != src) {
					path.push_back(ind);
					ind = parent[ind];
				}
				path.push_back(ind);
				path.insert(path.begin(), src);
				cout << path.size() << endl;
				for(auto num : path) cout << num << " ";
				return 0;
			}
		}
	}

	cout << "IMPOSSIBLE";
	return 0;
}