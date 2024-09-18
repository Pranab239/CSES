#include<bits/stdc++.h>
using namespace std;

bool reachBoundary(int row, int col, int n, int m) {
	return (row == 0 || col == 0 || row == n-1 || col == m-1);
}

bool BFS(vector<vector<int>>& monsters, vector<vector<char>>& matrix, pair<int,int>& src, 
	vector<vector<bool>>& vis, vector<vector<char>>& parent, int& source, int& dest) {
	
	queue<pair<int,int>> q;		// queue for the monsters
	queue<pair<int,int>> me;	// queue for the source

	// Put all the monsters in the queue, these are all the sources
	for(auto vec : monsters) {
		q.push({vec[0], vec[1]});
	}

	// put the source into the me queue
	me.push({src.first, src.second});

	int n = matrix.size();
	int m = matrix[0].size();
	int delRow[] = {-1, 0, 1, 0};
	int delCol[] = {0, 1, 0, -1};
	char direction[] = {'U', 'R', 'D', 'L'};

	while(!q.empty() || !me.empty()) {

		int size = q.size();
		// cout << "monster size: " << size << endl;
		while(size--) {
			int row = q.front().first;
			int col = q.front().second;
			q.pop();

			// One level complete for all the monsters
			for(int i = 0; i < 4; i++) {
				int nRow = row + delRow[i];
				int nCol = col + delCol[i];

				if(nRow < n && nRow >= 0 && nCol < m && nCol >= 0 && !vis[nRow][nCol]) {
					vis[nRow][nCol] = true;
					q.push({nRow, nCol});
				}
			}
		}

		size = me.size();
		// cout << "player size: " << size << endl;
		while(size--) {
			int row = me.front().first;
			int col = me.front().second;
			me.pop();

			// can reach to the boundary
			if(reachBoundary(row,col, n, m) && matrix[row][col] == '.') {
				source = row;
				dest = col;
				return true;
			}

			for(int i = 0; i < 4; i++) {
				int nRow = row + delRow[i];
				int nCol = col + delCol[i];

				if(nRow < n && nRow >= 0 && nCol < m && nCol >= 0 && !vis[nRow][nCol] && parent[nRow][nCol] == '_') {
					parent[nRow][nCol] = direction[i];
					me.push({nRow,nCol});
				}
			}
		}
	}

	return false;
}

int main() {
	int n; cin >> n;
	int m; cin >> m;
	vector<vector<int>> monsters;
	vector<vector<bool>> vis(n, vector<bool>(m, false));
	vector<vector<char>> matrix(n, vector<char>(m));
	vector<vector<char>> parent(n, vector<char>(m, '_'));
	pair<int,int> src;
	int source;
	int dest;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			cin >> matrix[i][j];
			if(matrix[i][j] == 'M' || matrix[i][j] == '#') {
				vis[i][j] = true;
			}
			if(matrix[i][j] == 'A') {
				src = {i, j};
				parent[i][j] = 'A';
			}
			else if(matrix[i][j] == 'M') {
				monsters.push_back({i,j});
			}
		}
	}

	// Player is already in the boundary
	if(reachBoundary(src.first, src.second, n, m) == true) {
		cout << "YES" << endl;
		cout << 0;
		return 0;
	}

	// Do a multisource BFS from all the monsters
	if(BFS(monsters, matrix, src, vis, parent, source, dest) == false) {
		cout << "NO";
		return 0;
	}
	cout << "YES" << endl;
	// for(auto vec : parent) {
	// 	for(auto ch : vec) {
	// 		cout << ch << " ";
	// 	}
	// 	cout << endl;
	// }
	// cout << source << " " << dest << endl;

	// Create the path form the boundary to the source A
	string path;
	while(1) {
		path.push_back(parent[source][dest]);

		if(parent[source][dest] == 'R') dest -= 1;
		else if(parent[source][dest] == 'D') source -= 1;
		else if(parent[source][dest] == 'U') source += 1;
		else if(parent[source][dest] == 'L') dest += 1;

		if(source == src.first && dest == src.second) break;
	}
	reverse(path.begin(), path.end());
	cout << path.length() << endl;
	cout << path;
	return 0;
}