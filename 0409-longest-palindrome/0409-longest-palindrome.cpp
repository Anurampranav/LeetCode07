class Solution {
public:
    int longestPalindrome(std::string s) {
        int freq[128] = {0};
        for (char c : s) {
            freq[c]++;
        }

        int length = 0;
        bool hasOdd = false;

        for (int count : freq) {
            if (count % 2 == 0) {
                length += count;
            } else {
                length += count - 1;
                hasOdd = true;
            }
        }

        return hasOdd ? length + 1 : length;
    }
};