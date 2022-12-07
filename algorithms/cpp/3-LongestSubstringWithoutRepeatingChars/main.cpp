//
// Created by Benjamin Lee on 12/6/22.
// https://leetcode.com/problems/longest-substring-without-repeating-characters/
//

/*
 *
 * The string can be comprised of English letters, digits, symbols, and spaces. We can use an array to capture the
 * counts of the ASCII characters in the string. An alternate data structure to hold counts is a hash map.
 *
 * There are a couple of approaches we can use to traverse the string.
 *
 * The brute force way can iterate across the string, using a double loop to iterate across the all the combinations.
 *
 * Time Complexity: O((n^2)
 * Space Complexity: O(m), where m = 128
 *
 * We can also use the sliding window to avoid a double loop. A sliding window works by defining a left and right
 * pointer (index in this case) to represent the left and right sides of the window. What we can track is the position
 * of the leftmost character. We know we hit a duplicate if the character entry in our index array is not -1 (-1 means
 * it hasn't been found) and it's position index is >= to the left edge and < the right. The entry always represents
 * the leftmost instance of the character in our window. And the window always holds at most only 1 instance of a char.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(m), where m = 128
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

class Solution {
public:
#ifdef BRUTE
    int lengthOfLongestSubstring(std::string s) {
        // Trivial rejection
        int len = s.length();
        if (len <= 1) {
            return len;
        }

        int longest = 0;

        for (int i=0;i<s.length();++i) {
            char counts[128] = {0};
            //counts[s[i]]++;

            for (int j=i;j<s.length();++j) {
                auto ch = s[j];
                if (counts[ch]) {
                    if ((j - i) > longest) {
                        longest = j - i;
                    }
                    break;
                }
                counts[ch]++;
                if ((j - i + 1) > longest) {
                    longest = j - i + 1;
                }
            }
        }

        return longest;
    }
#else
    int lengthOfLongestSubstring(std::string s) {
        int longest = 0;
        int left = 0, right = 0;
        std::vector<int> chars(128, -1);

        while (right < s.length()) {
            auto ch = s[right];
            auto index = chars[ch];
            if (index != -1 && index >= left && index < right) {
                left = index + 1;
            }
            longest = std::max(right - left + 1, longest);
            chars[ch] = right;
            ++right;
        }
        return longest;
    }
#endif /* BRUTE */
};

TEST_CASE("Longest Substring Without Repeating Characters", "algorithm") {
    Solution soln;
    const std::string testCase0 = "abcabcbb";
    const std::string testCase1 = "bbbbb";
    const std::string testCase2 = "pwwkew";
    const std::string testCase3 = "dvdf";
    const std::string testCase4 = "abba";
    const std::string testCase5 = "wobgrovw";

    CHECK(soln.lengthOfLongestSubstring(testCase5) == 6);
    CHECK(soln.lengthOfLongestSubstring(testCase0) == 3);
    CHECK(soln.lengthOfLongestSubstring(testCase1) == 1);
    CHECK(soln.lengthOfLongestSubstring(testCase2) == 3);
    CHECK(soln.lengthOfLongestSubstring(testCase3) == 3);
    CHECK(soln.lengthOfLongestSubstring(testCase4) == 2);
}
