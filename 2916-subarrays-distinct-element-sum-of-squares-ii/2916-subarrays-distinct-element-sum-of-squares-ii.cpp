class Solution {
    static const int MOD = 1e9 + 7;

    struct Node {
        long long sum_d = 0;
        long long sum_sq = 0;
        long long lazy = 0;
    };

    vector<Node> tree;

    void apply(int node, int start, int end, long long add) {
        long long len = end - start + 1;
        add %= MOD;
        
        tree[node].sum_sq = (tree[node].sum_sq + 2 * add * tree[node].sum_d % MOD + len * add % MOD * add % MOD) % MOD;
        tree[node].sum_d = (tree[node].sum_d + len * add) % MOD;
        tree[node].lazy = (tree[node].lazy + add) % MOD;
    }

    void push(int node, int start, int end) {
        if (tree[node].lazy == 0) return;
        
        long long add = tree[node].lazy;
        tree[node].lazy = 0;

        int mid = start + (end - start) / 2;
        apply(2 * node, start, mid, add);
        apply(2 * node + 1, mid + 1, end, add);
    }

    void update(int node, int start, int end, int l, int r, long long val) {
        if (l <= start && end <= r) {
            apply(node, start, end, val);
            return;
        }

        push(node, start, end);
        int mid = start + (end - start) / 2;

        if (l <= mid) update(2 * node, start, mid, l, r, val);
        if (r > mid) update(2 * node + 1, mid + 1, end, l, r, val);

        tree[node].sum_d = (tree[2 * node].sum_d + tree[2 * node + 1].sum_d) % MOD;
        tree[node].sum_sq = (tree[2 * node].sum_sq + tree[2 * node + 1].sum_sq) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        tree.assign(4 * n, Node());
        unordered_map<int, int> last_pos;

        long long total_ans = 0;

        for (int j = 0; j < n; ++j) {
            int k = last_pos.count(nums[j]) ? last_pos[nums[j]] : -1;
            
            update(1, 0, n - 1, k + 1, j, 1);
            total_ans = (total_ans + tree[1].sum_sq) % MOD;
            last_pos[nums[j]] = j;
        }

        return total_ans;
    }
};