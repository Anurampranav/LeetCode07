#include <vector>

class Solution {
private:
    long long dfs(std::vector<std::vector<int>>& grid, int r, int c, int m, int n) {
        // Boundary check and water/visited check
        if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == 0) {
            return 0;
        }

        // Add current cell value and mark it as visited by setting to 0
        long long sum = grid[r][c];
        grid[r][c] = 0;

        // Explore 4-directional neighbors
        sum += dfs(grid, r + 1, c, m, n);
        sum += dfs(grid, r - 1, c, m, n);
        sum += dfs(grid, r, c + 1, m, n);
        sum += dfs(grid, r, c - 1, m, n);

        return sum;
    }

public:
    int countIslands(std::vector<std::vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int validIslandCount = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // Found unvisited land
                if (grid[i][j] > 0) {
                    long long totalSum = dfs(grid, i, j, m, n);
                    
                    // Check if total island sum is divisible by k
                    if (totalSum % k == 0) {
                        validIslandCount++;
                    }
                }
            }
        }

        return validIslandCount;
    }
};