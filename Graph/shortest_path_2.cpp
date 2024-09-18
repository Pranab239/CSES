#include<bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	int m; cin >> m;
	int q; cin >> q;

	vector<vector<int>> edges(m, vector<int>(3));
	vector<vector<int>> queries(q, vector<int>(2));
	for(int i = 0; i < m; i++) {
		cin >> edges[i][0];
		cin >> edges[i][1];
		cin >> edges[i][2];
	}
	for(int i = 0; i < q; i++) {
		cin >> queries[i][0];
		cin >> queries[i][1];
	}


	vector<vector<long long>> matrix(n+1, vector<long long>(n+1, 1e15));
	for(auto vec : edges) {
		int u = vec[0];
		int v = vec[1];
		long long d = vec[2];

		matrix[u][v] = min(matrix[u][v], d);
		matrix[v][u] = min(matrix[v][u], d);
	}

	for(int via = 1; via < n+1; via++) {
		for(int j = 1; j < n+1; j++) {
			for(int k = 1; k < n+1; k++) {
				if(j == k) matrix[j][k] = 0;
				else matrix[j][k] = min(matrix[j][via] + matrix[via][k], matrix[j][k]);
			}
		}
	}

	// for(int i = 1; i < n+1; i++) {
	// 	for(int j = 1; j <= n; j++) {
	// 		cout << matrix[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }

	for(int i = 0; i < q; i++) {
		if(matrix[queries[i][0]][queries[i][1]] == 1e15) cout << -1 << endl;
		else cout << matrix[queries[i][0]][queries[i][1]] << endl;
	}

	return 0;
}