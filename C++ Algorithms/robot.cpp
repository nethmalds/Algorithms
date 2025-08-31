#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int findShortestPath(const vector<vector<char>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    
    // Find start and goal positions
    pair<int, int> start, goal;
    bool foundStart = false, foundGoal = false;
    
    for (int i = 0; i < rows && (!foundStart || !foundGoal); ++i) {
        for (int j = 0; j < cols && (!foundStart || !foundGoal); ++j) {
            if (grid[i][j] == 'S') {
                start = {i, j};
                foundStart = true;
            } else if (grid[i][j] == 'G') {
                goal = {i, j};
                foundGoal = true;
            }
        }
    }
    
    // Direction vectors for 4-directional movement (up, down, left, right)
    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};
    
    // BFS setup
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<int>> distance(rows, vector<int>(cols, 0));
    
    // Start BFS from starting position
    q.push(start);
    visited[start.first][start.second] = true;
    distance[start.first][start.second] = 0;
    
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        
        // Check if we reached the goal
        if (x == goal.first && y == goal.second) {
            return distance[x][y];
        }
        
        // Explore all 4 directions
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            // Check bounds
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                // Check if cell is not an obstacle and not visited
                if (!visited[nx][ny] && grid[nx][ny] != '#') {
                    visited[nx][ny] = true;
                    distance[nx][ny] = distance[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
    }
    
    // No path found
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int R, C;
    cin >> R >> C;
    
    vector<vector<char>> grid(R, vector<char>(C));
    
    // Read the grid
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            cin >> grid[i][j];
        }
    }
    
    // Find and output the shortest path length
    cout << findShortestPath(grid) << endl;
    
    return 0;
}