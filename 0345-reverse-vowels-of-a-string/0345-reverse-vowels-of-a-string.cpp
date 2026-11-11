#include <string>

class Solution {
public:
    string reverseVowels(string s) {
        // Fast lookup table for all 256 ASCII characters
        bool isVowel[256] = {false};
        for (char c : "aeiouAEIOU") {
            if (c != '\0') isVowel[static_cast<unsigned char>(c)] = true;
        }

        int left = 0;
        int right = s.length() - 1;

        while (left < right) {
            while (left < right && !isVowel[static_cast<unsigned char>(s[left])]) {
                left++;
            }
            while (left < right && !isVowel[static_cast<unsigned char>(s[right])]) {
                right--;
            }

            if (left < right) {
                std::swap(s[left], s[right]);
                left++;
                right--;
            }
        }

        return s;
    }
};