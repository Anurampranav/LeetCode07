class Solution {
public:
    int minCost(std::vector<std::vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        // dp[r][c] stores all reachable XOR values at position (r, c)
        std::vector<std::vector<std::unordered_set<int>>> dp(m, std::vector<std::unordered_set<int>>(n));
        
        dp[0][0].insert(grid[0][0]);
        
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (r == 0 && c == 0) continue;
                
                // Transition from top cell (r - 1, c)
                if (r > 0) {
                    for (int prev_val : dp[r - 1][c]) {
                        dp[r][c].insert(prev_val ^ grid[r][c]);
                    }
                }
                
                // Transition from left cell (r, c - 1)
                if (c > 0) {
                    for (int prev_val : dp[r][c - 1]) {
                        dp[r][c].insert(prev_val ^ grid[r][c]);
                    }
                }
            }
        }
        
        // Find the minimum XOR sum in the bottom-right cell
        int min_xor = INT_MAX;
        for (int val : dp[m - 1][n - 1]) {
            min_xor = std::min(min_xor, val);
        }
        
        return min_xor;
    }
};