#include<bits/stdc++.h>
using namespace std;

void DFS(int row, int col, vector<vector<char>>& grid, vector<vector<bool>>& vis) {
	vis[row][col] = true;
	int delRow[] = {-1, 0, 1, 0};
	int delCol[] = {0, 1, 0, -1};
	int n = grid.size();
	int m = grid[0].size();

	for(int i = 0; i < 4; i++) {
		int nRow = row + delRow[i];
		int nCol = col + delCol[i];
		
		if(nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && !vis[nRow][nCol] && grid[nRow][nCol] == '.') {
			DFS(nRow, nCol, grid, vis);
		}
	}
}

int main() {
	int n; cin >> n;
	int m; cin >> m;

	vector<vector<char>> grid(n, vector<char>(m));
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			cin >> grid[i][j];
		}
	}

	vector<vector<bool>> visited(n, vector<bool>(m, false));
	int count = 0;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(grid[i][j] == '.' && visited[i][j] == false) {
				count += 1;
				DFS(i, j, grid, visited);
			}
		}
	}
	cout << count;
}
