#include<bits/stdc++.h>
using namespace std;

int main() {
	int V; cin >> V;
	int E; cin >> E;

	vector<vector<int>> edges(E, vector<int>(2));
	for(int i = 0; i < E; i++) {
		cin >> edges[i][0];
		cin >> edges[i][1];
	}

	vector<int> adjList[V+1];
	for(int i = 0; i < E; i++) {
		adjList[edges[i][0]].push_back(edges[i][1]);
		adjList[edges[i][1]].push_back(edges[i][0]);
	}

	vector<int> vis(V+1, false);
	vector<int> parent(V+1, 0);
	for(int i = 0; i < V+1; i++) parent[i] = i;

	queue<int> q;
	q.push(1);
	vis[1] = true;

	while(!q.empty()) {
		int node = q.front();
		q.pop();

		if(node == V) break;

		for(auto adjNode : adjList[node]) {
			if(!vis[adjNode]) {
				vis[adjNode] = true;
				parent[adjNode] = node;
				q.push(adjNode);
			}
		}
	}

	if(parent[V] == V) {
		cout << "IMPOSSIBLE";
	}
	else {
		vector<int> path;
		int ind = V;
		while(ind != parent[ind]) {
			path.push_back(ind);
			ind = parent[ind];
		}
		path.push_back(ind);
		cout << path.size() << endl;
		while(path.size() > 0) {
			cout << path.back() << " ";
			path.pop_back();
		}
	}
}