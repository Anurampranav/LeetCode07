class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> freq;

        for (int i = 0; i < nums.size(); i++) {
            if (freq.count(nums[i])) {
                return true;
            }

            freq.insert(nums[i]);
        }

        return false;
    }
};