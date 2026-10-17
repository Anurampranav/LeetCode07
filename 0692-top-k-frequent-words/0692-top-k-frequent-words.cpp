class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map< string ,int > freq;
         

        for(string word:words){
            freq[word]++;

        }

        vector<pair< string , int>> v;

        for(auto x : freq){
            v.push_back({x.first , x.second});

        }

        sort(v.begin(), v.end(), [](auto a, auto b) {
            if(a.second != b.second){
                return a.second > b.second;

            }
            return a.first<b.first;
        });

        vector<string> ans;

        for(int i= 0 ; i < k ; i++){
            ans.push_back(v[i].first);

        }
        return ans;
    }

};