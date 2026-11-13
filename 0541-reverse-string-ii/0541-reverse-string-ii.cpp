class Solution {
public:
    string reverseStr(string s, int k) {
        const int n = s.size();
        const int step = 2 * k;
        
        for (int i = 0; i < n; i += step) {
            reverse(s.begin() + i, s.begin() + min(i + k, n));
        }
        
        return s;
    }
};