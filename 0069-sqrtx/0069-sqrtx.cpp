class Solution {
public:
    int mySqrt(int x) {
        if (x < 2) return x; // Handles 0 and 1 directly

        int left = 1, right = x / 2;
        int ans = 0;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            long long sq = (long long)mid * mid; // Prevent integer overflow

            if (sq == x) {
                return mid;
            } else if (sq < x) {
                ans = mid;       // mid is a valid candidate; look for a larger one
                left = mid + 1;
            } else {
                right = mid - 1; // mid^2 is too big; search the left half
            }
        }

        return ans;
    }
};