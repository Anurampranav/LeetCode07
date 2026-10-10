class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        long long k = (long long)k1 + k2;
        
        int max_diff = 0;
        vector<int> diffs(n);
        for (int i = 0; i < n; ++i) {
            diffs[i] = abs(nums1[i] - nums2[i]);
            max_diff = max(max_diff, diffs[i]);
        }
        
        vector<long long> freq(max_diff + 1, 0);
        for (int d : diffs) {
            freq[d]++;
        }
        
        for (int d = max_diff; d > 0 && k > 0; --d) {
            if (freq[d] == 0) continue;
            
            long long take = min(k, freq[d]);
            freq[d] -= take;
            freq[d - 1] += take;
            k -= take;
        }
        
        long long ans = 0;
        for (long long d = 1; d <= max_diff; ++d) {
            if (freq[d] > 0) {
                ans += freq[d] * d * d;
            }
        }
        
        return ans;
    }
};