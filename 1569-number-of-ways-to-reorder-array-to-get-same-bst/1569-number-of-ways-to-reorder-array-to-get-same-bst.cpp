class Solution {
public:
    static const int MOD = 1000000007;
    vector<vector<long long>> C;

    long long solve(vector<int>& a) {
        int n = a.size();
        if (n <= 2) return 1;
        vector<int> L, R;
        for (int i = 1; i < n; i++) {
            if (a[i] < a[0]) L.push_back(a[i]);
            else R.push_back(a[i]);
        }
        long long res = C[n - 1][L.size()] % MOD;
        res = res * solve(L) % MOD;
        res = res * solve(R) % MOD;
        return res;
    }

    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        C.assign(n + 1, vector<long long>(n + 1, 0));
        for (int i = 0; i <= n; i++) {
            C[i][0] = 1;
            for (int j = 1; j <= i; j++)
                C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
        long long total = solve(nums);
        return (int)((total - 1 + MOD) % MOD);
    }
};