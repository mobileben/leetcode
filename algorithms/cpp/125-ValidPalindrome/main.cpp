//
// Created by Benjamin Lee on 12/9/22.
// https://leetcode.com/problems/valid-palindrome/
//

/*
 * Brute force would be to build a new string based on the filtering out the invalid characters. Once could then reverse
 * the string and compare with the filtered string.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * A better way is to have moving pointers going from left to right and right to left.
 *
 * Time Complexity: O(n/2)
 * Space Complexity: O(1)
 */
#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

class Solution {
public:
    bool isPalindrome(std::string s) {
        if (s.empty()) return true;
        int left = 0, right = s.length() - 1;
        char lch, rch;

        while (left <= right) {
            // Find next valid lch
            while (left < s.length() && !std::isalnum(s[left])) {
                ++left;
            }

            // Find next valid rch
            while (right >= 0 && !std::isalnum(s[right])) {
                --right;
            }

            if (left <= right) {
                if (std::tolower(s[left]) != std::tolower(s[right])) {
                    return false;
                }
            } else {
                break;
            }

            ++left;
            --right;
        }

        return true;
    }
};

TEST_CASE("ValidPalindrome", "algorithms") {
    Solution soln;
    std::string testCase0 = "";
    std::string testCase1 = " ";
    std::string testCase2 = "a";
    std::string testCase3 = "aba";
    std::string testCase4 = "abba";
    std::string testCase5 = "a  b,, b a";
    std::string testCase6 = "a  b,, c a";

    bool actual4 = soln.isPalindrome(testCase4);
    bool actual0 = soln.isPalindrome(testCase0);
    bool actual1 = soln.isPalindrome(testCase1);
    bool actual2 = soln.isPalindrome(testCase2);
    bool actual3 = soln.isPalindrome(testCase3);
    bool actual5 = soln.isPalindrome(testCase5);
    bool actual6 = soln.isPalindrome(testCase6);

    CHECK(actual0 == true);
    CHECK(actual1 == true);
    CHECK(actual2 == true);
    CHECK(actual3 == true);
    CHECK(actual4 == true);
    CHECK(actual5 == true);
    CHECK(actual6 == false);

}

