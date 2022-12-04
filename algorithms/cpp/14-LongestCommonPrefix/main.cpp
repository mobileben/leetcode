//
// Created by Benjamin Lee on 12/3/22.
// https://leetcode.com/problems/longest-common-prefix/
//

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#define BRUTE

class Solution {
public:
#ifdef BRUTE
    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        // Trivial rejection
        if (strs.empty()) {
            return "";
        } else if (strs.size() == 1) {
            return strs.front();
        }

        auto& first = strs.front();
        auto len = first.length();
        // We need to check our first string against *all* other strings
        // Possible cases that come up for rejection are
        //  first string is smaller than other string
        //  other string character is smaller than first string
        //  other string current char != first string char
        for (auto i=0;i<len;++i) {
            for (auto j=1;j<strs.size();++j) {
                auto& curr = strs[j];
                if (curr.length() < i) {
                    len = i;
                    break;
                }
                if (curr[i] != first[i]) {
                    len = i;
                    break;
                }
            }
        }

        return first.substr(0, len);
    }
#else
    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        // Trivial rejection
        if (strs.empty()) {
            return "";
        } else if (strs.size() == 1) {
            return strs.front();
        }

        std::sort(strs.begin(), strs.end());
        auto& first = strs.front();
        auto len = first.length();
        // We need to check our first string against *all* other strings
        // Possible cases that come up for rejection are
        //  first string is smaller than other string
        //  other string character is smaller than first string
        //  other string current char != first string char
        for (auto i=0;i<len;++i) {
            for (auto j=1;j<strs.size();++j) {
                auto& curr = strs[j];
                if (curr.length() < i) {
                    len = i;
                    break;
                }
                if (curr[i] != first[i]) {
                    len = i;
                    break;
                }
            }
        }

        return first.substr(0, len);
    }
#endif /* BRUTE */
};

TEST_CASE("LongestCommonPrefix", "algorithm") {
    Solution soln;
    std::vector<std::string> testCase0 = {""};
    std::vector<std::string> testCase1 = {"a"};
    std::vector<std::string> testCase2 = {"a", ""};
    std::vector<std::string> testCase3 = {"", "a"};
    std::vector<std::string> testCase4 = {"a", "aa"};
    std::vector<std::string> testCase5 = {"a", "ab", "a"};
    std::vector<std::string> testCase6 = {"ab", "ab", "a"};
    std::vector<std::string> testCase7 = {"ab", "abc", "ac"};
    std::vector<std::string> testCase8 = {"ab", "abc", "abc"};
    std::vector<std::string> testCase9 = {"abc", "abc", "ab"};
    std::vector<std::string> testCase10 = {"flower", "flow", "flight"};
    std::vector<std::string> testCase11 = {"dog", "racecar", "car"};

    CHECK(soln.longestCommonPrefix(testCase6) == "a");
    CHECK(soln.longestCommonPrefix(testCase0) == "");
    CHECK(soln.longestCommonPrefix(testCase1) == "a");
    CHECK(soln.longestCommonPrefix(testCase2) == "");
    CHECK(soln.longestCommonPrefix(testCase3) == "");
    CHECK(soln.longestCommonPrefix(testCase4) == "a");
    CHECK(soln.longestCommonPrefix(testCase5) == "a");
    CHECK(soln.longestCommonPrefix(testCase6) == "a");
    CHECK(soln.longestCommonPrefix(testCase7) == "a");
    CHECK(soln.longestCommonPrefix(testCase8) == "ab");
    CHECK(soln.longestCommonPrefix(testCase9) == "ab");
    CHECK(soln.longestCommonPrefix(testCase10) == "fl");
    CHECK(soln.longestCommonPrefix(testCase11) == "");
}