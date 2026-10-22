class Solution {
public:
    int minOperations(std::vector<int>& nums) {
        int n = nums.size();
        
        // Find index of value 0
        int zero = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 0) {
                zero = i;
                break;
            }
        }
        
        // Helper to check if array is cyclically sorted with given direction step (+1 or -1)
        auto isValid = [&](int step) -> bool {
            for (int i = 1; i < n; ++i) {
                int prevIdx = (zero + (i - 1) * step % n + n) % n;
                int currIdx = (zero + i * step % n + n) % n;
                if (nums[prevIdx] > nums[currIdx]) {
                    return false;
                }
            }
            return true;
        };

        int ans = INT_MAX;

        // Check cyclically increasing
        if (isValid(1)) {
            ans = std::min({ans, zero, n - zero + 2});
        }

        // Check cyclically decreasing
        if (isValid(-1)) {
            ans = std::min({ans, zero + 2, n - zero});
        }

        return (ans == INT_MAX) ? -1 : ans;
    }
};