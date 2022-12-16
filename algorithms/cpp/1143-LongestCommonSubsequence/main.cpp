//
// Created by Benjamin Lee on 12/14/22.
// https://leetcode.com/problems/longest-common-subsequence/
//

/*
 * The key element here is that the order needs to be maintained. For example
 * text1: "ace"
 * text2: "ace"
 *
 * has a subsequence of "ace", however
 *
 * text1: "ace"
 * text2: "eca"
 *
 * has a subsequence of only "c".
 *
 * A subsequence is defined as a new string generated from text1 with some or none of the characters deleted without
 * changing the relative order of the remaining characters.
 *
 * Due to this restriction, we can't attack this with something like a hashmap.
 *
 * Brute force for this would be very time intensive. One could also try and Greedy algorithm, but at least from first
 * glance, generating one is potentially complicated.
 *
 * This is a dynamic programming question, because we can use previous answers to solve this.
 *
 * There are two DP approaches one could take: memoization (top down) and tabulation (bottom up). Memoization is typicaly
 * recursive whereas tabulation is typically iterative.
 *
 * For tabulation, we have two cases we need to deal with
 * - When text[i] == text2[j], then we set the value of dp[i][j] = 1 + dp[i+1][j+1]
 * - Else we set dp[i][j] = std::max(dp[i+1][j], dp[i][j+1])
 *
 *  Awe we may go out of bounds, we need dp to be m + 1 x n + 1
 *
 *  Time Complexity: O(mn)
 *  Space Complexity: O(mn)
 *
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

class Solution {
public:
    int longestCommonSubsequence(std::string text1, std::string text2) {
        int m = text1.size(), n = text2.size();
        std::vector<std::vector<int>> dp(m+1, std::vector<int>(n+1));

        for (int i=m-1;i>=0;--i) {
            for (int j=n-1;j>=0;--j) {
                if (text1[i] == text2[j]) {
                   dp[i][j] = 1 + dp[i+1][j+1];
                } else {
                    dp[i][j] = std::max(dp[i+1][j], dp[i][j+1]);
                }
            }
        }

        return dp[0][0];
    }
};

TEST_CASE("LongestCommonSubsequence", "algorithm") {
    Solution soln;
    std::string testCase0_0 = "a";
    std::string testCase1_0 = "a";
    std::string testCase0_1 = "a";
    std::string testCase1_1 = "b";
    std::string testCase0_2 = "abba";
    std::string testCase1_2 = "abb";
    std::string testCase0_3 = "abcde";
    std::string testCase1_3 = "ace";
    std::string testCase0_4 = "abc";
    std::string testCase1_4 = "abc";
    std::string testCase0_5 = "abc";
    std::string testCase1_5 = "def";
    std::string testCase0_6 = "ezupkr";
    std::string testCase1_6 = "ubmrapg";
    std::string testCase0_7 = "ace";
    std::string testCase1_7 = "eca";
    std::string testCase0_8 = "ace";
    std::string testCase1_8 = "ade";

    CHECK(soln.longestCommonSubsequence(testCase0_6, testCase1_6) == 2);
    CHECK(soln.longestCommonSubsequence(testCase0_0, testCase1_0) == 1);
    CHECK(soln.longestCommonSubsequence(testCase0_1, testCase1_1) == 0);
    CHECK(soln.longestCommonSubsequence(testCase0_2, testCase1_2) == 3);
    CHECK(soln.longestCommonSubsequence(testCase0_3, testCase1_3) == 3);
    CHECK(soln.longestCommonSubsequence(testCase0_4, testCase1_4) == 3);
    CHECK(soln.longestCommonSubsequence(testCase0_5, testCase1_5) == 0);
    CHECK(soln.longestCommonSubsequence(testCase0_7, testCase1_7) == 1);
    CHECK(soln.longestCommonSubsequence(testCase0_8, testCase1_8) == 2);
}

