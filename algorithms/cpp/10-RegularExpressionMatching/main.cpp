//
// Created by Benjamin Lee on 12/9/22.
// https://leetcode.com/problems/regular-expression-matching/
// Hard
//

/*
 * Only regular pattern charcters are '.' and '*' where
 * - '.' matches a single character
 * - '*' matches zero or more of the preceding element
 *
 * Observations
 *
 * ".*" would match any character, as it means "zero or more of any character"
 * - "*" as the string is illegal, as '*' must be preceded by a character
 * - Some interesting cases will occur
 *      - s="a" and p=".*" would be true
 *      - s="ab" and p=".*b" would be true
 *      - s="ab" and p="a.*" would be true
 *
 * Need to determine which cases degrade to any
 *
 * We should look at this like a state machine
 * ".*.*" == ".*"
 * ".*." == ".*"
 * ".*.." == ".*"
 * ".*." == ".*"
 *
 * Illegals
 * "**"
 * ".**"
 * "*"
 *
 * - match (must consume one)
 * - anyChar (must consume one)
 * - preceding (must have preceding, zero or more, look at trailing to change mode))
 * - precedingWithAny (zero or more, look at trailing to changemode)
 *
 * Other interesting rules are if we encounter successive ".*", we must consume them all. For example, if p = ".*.*",
 * we would consume all of the patterns and be in the precedingWithAny mode.
 *
 * We can fill a table so we can to cache the results of substrings. When we populate, we have the following rules to
 * consider
 * 1. if s[i] == p[j] or if p[j] == '.', then dp[i][j] = dp[i-1][j-1]
 * 2. if p[j] == '*', dp[i][j] = dp[i][j-2] OR if s[i] == p[j-1] or p[j-1] == '.', dp[i][j] = dp[i][j] | dp[i-1][j]
 *
 * Time Complexity: O(mn)
 * Space Complexity: O(mn) (really it is is (m + 1) * (n + 1))
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <deque>

class Solution {
public:
    bool isMatch(std::string s, std::string p) {
        std::vector<std::vector<bool>> dp(s.size() + 1, std::vector<bool>(p.size() + 1));

        // Empty string and empty pattern is a match
        dp[0][0] = true;

        // Handle variations of * (eg. a*b*) across empty strings
        for (int i=1;i<dp[0].size();++i) {
            if (p[i-1] == '*' && i-2 >= 0) {
                dp[0][i] = dp[0][i-2];
            }
        }

        for (int i=1;i<dp.size();++i) {
            for (int j=1;j<dp[0].size();++j) {
                if (p[j-1] == '.' || p[j-1] == s[i-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else if (p[j-1] == '*' && j-2 >= 0) {
                    dp[i][j] = dp[i][j-2];
                    if (p[j-2] == '.' || p[j-2] == s[i-1]) {
                        dp[i][j] = dp[i][j] | dp[i-1][j];
                    }
                }
            }
        }
        return dp[s.size()][p.size()];
    }
};

TEST_CASE("RegularExpressionMatching", "algorithm") {
    Solution soln;
    std::string testCaseS_0 = "aa";
    std::string testCaseP_0 = "a";
    std::string testCaseS_1 = "aa";
    std::string testCaseP_1 = "a*";
    std::string testCaseS_2 = "aab";
    std::string testCaseP_2 = "a*";
    std::string testCaseS_3 = "ant";
    std::string testCaseP_3 = ".n.";
    std::string testCaseS_4 = "aab";
    std::string testCaseP_4 = ".*";
    std::string testCaseS_5 = "a";
    std::string testCaseP_5 = "a.";
    std::string testCaseS_6 = "abdsfdsz";
    std::string testCaseP_6 = "a.*sf";
    std::string testCaseS_7 = "abdsfdsz";
    std::string testCaseP_7 = "a.*sf.*";
    std::string testCaseS_8 = "a";
    std::string testCaseP_8 = ".*";
    std::string testCaseS_9 = "ab";
    std::string testCaseP_9 = ".*b";
    std::string testCaseS_10 = "ab";
    std::string testCaseP_10 = "a.*";
    std::string testCaseS_11 = "a";
    std::string testCaseP_11 = ".*.*";
    std::string testCaseS_12 = "abab";
    std::string testCaseP_12 = ".*b.*";
    std::string testCaseS_13 = "abcdef";
    std::string testCaseP_13 = ".*.*bcdef";
    std::string testCaseS_14 = "ab";
    std::string testCaseP_14 = "**";
    std::string testCaseS_15 = "b";
    std::string testCaseP_15 = ".*.b";
    std::string testCaseS_16 = "aab";
    std::string testCaseP_16 = "c*a*b";

    auto actual0 = soln.isMatch(testCaseS_0, testCaseP_0);
    auto actual1 = soln.isMatch(testCaseS_1, testCaseP_1);
    auto actual2 = soln.isMatch(testCaseS_2, testCaseP_2);
    auto actual3 = soln.isMatch(testCaseS_3, testCaseP_3);
    auto actual4 = soln.isMatch(testCaseS_4, testCaseP_4);
    auto actual5 = soln.isMatch(testCaseS_5, testCaseP_5);
    auto actual6 = soln.isMatch(testCaseS_6, testCaseP_6);
    auto actual7 = soln.isMatch(testCaseS_7, testCaseP_7);
    auto actual8 = soln.isMatch(testCaseS_8, testCaseP_8);
    auto actual9 = soln.isMatch(testCaseS_9, testCaseP_9);
    auto actual10 = soln.isMatch(testCaseS_10, testCaseP_10);
    auto actual11 = soln.isMatch(testCaseS_11, testCaseP_11);
    auto actual12 = soln.isMatch(testCaseS_12, testCaseP_12);
    auto actual13 = soln.isMatch(testCaseS_13, testCaseP_13);
    auto actual14 = soln.isMatch(testCaseS_14, testCaseP_14);
    auto actual15 = soln.isMatch(testCaseS_15, testCaseP_15);
    auto actual16 = soln.isMatch(testCaseS_16, testCaseP_16);

    CHECK(actual0 == false);
    CHECK(actual1 == true);
    CHECK(actual2 == false);
    CHECK(actual3 == true);
    CHECK(actual4 == true);
    CHECK(actual5 == false);
    CHECK(actual6 == false);
    CHECK(actual7 == true);
    CHECK(actual8 == true);
    CHECK(actual9 == true);
    CHECK(actual10 == true);
    CHECK(actual11 == true);
    CHECK(actual12 == true);
    CHECK(actual13 == true);
    CHECK(actual14 == false);
    CHECK(actual15 == false);
    CHECK(actual16 == true);
}
