#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

class FenwickTree {
    int n;
    std::vector<int> tree;
public:
    FenwickTree(int n) : n(n), tree(n + 1, 0) {}

    void update(int i, int delta) {
        for (; i <= n; i += i & -i) {
            tree[i] ^= delta;
        }
    }

    void updateRange(int l, int r, int delta) {
        update(l, delta);
        update(r + 1, delta);
    }

    int query(int i) {
        int sum = 0;
        for (; i > 0; i -= i & -i) {
            sum ^= tree[i];
        }
        return sum;
    }
};

class Solution {
    int timer = 0;
    std::vector<int> in, out, depth;
    std::vector<std::vector<int>> up;
    int LOG = 17;

    void dfs(int u, int p, int d, const std::vector<std::vector<int>>& adj, const std::string& s, std::vector<int>& pathXor) {
        in[u] = ++timer;
        depth[u] = d;
        up[u][0] = p;
        for (int i = 1; i < LOG; ++i) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }

        int mask = 1 << (s[u] - 'a');
        pathXor[u] = (p == u ? 0 : pathXor[p]) ^ mask;

        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u, d + 1, adj, s, pathXor);
            }
        }
        out[u] = timer;
    }

    int getLCA(int u, int v) {
        if (depth[u] < depth[v]) std::swap(u, v);
        for (int i = LOG - 1; i >= 0; --i) {
            if (depth[u] - (1 << i) >= depth[v]) {
                u = up[u][i];
            }
        }
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; --i) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }

public:
    std::vector<bool> palindromePath(int n, std::vector<std::vector<int>>& edges, std::string s, std::vector<std::string>& queries) {
        std::vector<std::vector<int>> adj(n);
        for (const auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        timer = 0;
        in.resize(n);
        out.resize(n);
        depth.resize(n);
        up.assign(n, std::vector<int>(LOG, 0));
        std::vector<int> initialPathXor(n, 0);

        dfs(0, 0, 0, adj, s, initialPathXor);

        FenwickTree ft(n);
        for (int i = 0; i < n; ++i) {
            ft.updateRange(in[i], in[i], initialPathXor[i]);
        }

        std::vector<char> currChar(s.begin(), s.end());
        std::vector<bool> ans;

        for (const auto& q : queries) {
            std::stringstream ss(q);
            std::string type;
            ss >> type;
            
            if (type == "update") {
                int u;
                char c;
                ss >> u >> c;
                
                int oldMask = 1 << (currChar[u] - 'a');
                int newMask = 1 << (c - 'a');
                int delta = oldMask ^ newMask;
                
                currChar[u] = c;
                ft.updateRange(in[u], out[u], delta);
            } else {
                int u, v;
                ss >> u >> v;
                
                int lca = getLCA(u, v);
                
                int xorU = ft.query(in[u]);
                int xorV = ft.query(in[v]);
                int nodeLCAMask = 1 << (currChar[lca] - 'a');
                
                int pathMask = xorU ^ xorV ^ nodeLCAMask;
                
                ans.push_back((pathMask & (pathMask - 1)) == 0);
            }
        }

        return ans;
    }
};