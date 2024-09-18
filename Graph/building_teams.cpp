#include<bits/stdc++.h>
using namespace std;

bool BFS(int node, vector<int>& color, vector<int> adjList[]) {
	queue<int> q;
	q.push(node);
	color[node] = 1;

	while(!q.empty()) {
		int node = q.front();
		q.pop();

		for(auto adjNode : adjList[node]) {
			if(color[adjNode] == -1) {
				color[adjNode] = 3 - color[node];
				q.push(adjNode);
			}
			if(color[adjNode] == color[node])
				return false;
		}
	}

	return true;
}

// Graph Coloring Problem
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

	vector<int> color(V+1, -1);
	bool possible = true;
	for(int i = 1; i < V+1; i++) {
		if(color[i] == -1) {
			if(BFS(i, color, adjList) == false) {
				possible = false;
				break;
			}
		}
	}

	if(possible == false)
		cout << "IMPOSSIBLE";
	else {
		for(int i = 1; i < V+1; i++) cout << color[i] << " ";
	}
}