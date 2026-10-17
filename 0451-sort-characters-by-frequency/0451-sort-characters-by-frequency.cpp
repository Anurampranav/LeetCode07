class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char,int> freq;

        for(char c : s){
            freq[c]++;

        }

        vector<pair<char,int>> v;

        for(auto x : freq){
            v.push_back({x.first, x.second});
        }

        sort(v.begin(), v.end(),[](auto a, auto b){
            return a.second>b.second;
        });

        string ans = "";

        for(auto x:v ){
            for(int i = 0 ; i < x.second;i++){
                ans+= x.first;
            }
        }
        return ans;
        
    }
};