#include<bits/stdc++.h>
using namespace std;

bool BFS(int row, int col, vector<vector<char>>& direction, vector<vector<char>>& grid, string& path, vector<vector<bool>>& vis) {
	queue<pair<int,int>> q;
	int n = grid.size();
	int m = grid[0].size();

	vis[row][col] = true;
	q.push({row,col});

	int delRow[] = {-1, 0, 1, 0};
	int delCol[] = {0, 1, 0, -1};
	char move[] = {'U', 'R', 'D', 'L'};

	while(!q.empty()) {
		int r = q.front().first;
		int c = q.front().second;
		q.pop();

		if(grid[r][c] == 'B') {
			while(1) {
				path.push_back(direction[r][c]);
				
				// Tracing backward so opposite direction movement
				if(path.back() == 'L') c++;
				if(path.back() == 'R') c--;
				if(path.back() == 'U') r++;
				if(path.back() == 'D') r--;

				if(r == row && c == col) break;
			}
			return true;	// path found
		}
		
		for(int i = 0; i < 4; i++) {
			int nRow = r + delRow[i];
			int nCol = c + delCol[i];

			if(nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && !vis[nRow][nCol] && grid[nRow][nCol] != '#') {
				q.push({nRow,nCol});
				vis[nRow][nCol] = true;
				direction[nRow][nCol] = move[i];
			}
		}
	}
	return false;
}


int main() {
	int n; cin >> n;
	int m; cin >> m;

	int startI = -1;
	int startJ = -1;
	vector<vector<char>> grid(n, vector<char>(m));
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			cin >> grid[i][j];
			if(grid[i][j] == 'A') {
				startI = i;
				startJ = j;
			}
		}
	}
	
	vector<vector<char>> direction(n, vector<char>(m, '-'));	// store the direction from which the cell has been reached
	vector<vector<bool>> vis(n, vector<bool>(m, false));
	string path = "";

	if(BFS(startI, startJ, direction, grid, path, vis) == true) {
		cout << "YES" << endl;
		cout << path.length() << endl;
		reverse(path.begin(), path.end());
		cout << path;
	}
	else {
		cout << "NO";
	}
}
