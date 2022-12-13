//
// Created by Benjamin Lee on 12/11/22.
// https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/
//

/*
 * Brute force method for this is pretty straight forward, just iterating through both haystack and needle.
 *
 * Time Complexity: O(n*m)
 * SpaceComplexity: O(1)
 *
 * There is a method called Knuth-Morris-Pratt (KMP) that can be applied.
 * http://jakeboxer.com/blog/2009/12/13/the-knuth-morris-pratt-algorithm-in-my-own-words/
 * https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/
 *
 * Time Complexity: O(n*m)
 * SpaceComplexity: O(m)
 *
 */
#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

class Solution {
public:
#ifdef BRUTE
    int strStr(std::string haystack, std::string needle) {
        int h = haystack.size();
        int n = needle.size();
        for (int i=0;i<=(h - n);++i) {
            int j = 0;
            for (;j<n;++j) {
                if (haystack[i+j] != needle[j]) {
                    break;
                }
            }
            if (j == n) {
                return i;
            }
        }

        return -1;
    }
#else
    void buildLps(std::string& needle, std::vector<int>& lps) {
        int len = 0;

        lps[0] = 0; // First element is always 0

        int i = 1;
        while (i < needle.size()) {
            if (needle[i] == needle[len]) {
                lps[i++] = ++len;
            } else if (len) {
                len = lps[len-1];
            } else {
               lps[i++] = 0;
            }
        }
    }

    int strStr(std::string haystack, std::string needle) {
        int h = haystack.size();
        int n = needle.size();
        std::vector<int> lps(n);

        buildLps(needle, lps);

        int i = 0, j = 0;
        for (int i=0, j=0;i<h;) {
            if (haystack[i] == needle[j]) {
                ++i;
                ++j;
            }
            if (j == n) {
                return i - j;
            }
            if (i < h && haystack[i] != needle[j]) {
                if (j) {
                    j = lps[j - 1];
                } else {
                    ++i;
                }
            }
        }

        return -1;
    }
#endif /* BRUTE */
};

TEST_CASE("FindIndexOfFirstOccurrenceInString", "algorithm") {
    Solution soln;
    std::string haystack0 = "sadbutsad";
    std::string needle0 = "sad";
    std::string haystack1 = "leetcode";
    std::string needle1 = "leeto";
    std::string haystack2 = "yesthisisasentencefromawhileback";
    std::string needle2 = "a";
    std::string haystack3 = "elephant";
    std::string needle3 = "epe";
    std::string haystack4 = "a";
    std::string needle4 = "a";
    std::string haystack5 = "aaa";
    std::string needle5 = "aaaa";
    std::string haystack6 = "mississippi";
    std::string needle6 = "mississippii";

    CHECK(soln.strStr(haystack0, needle0) == 0);
    CHECK(soln.strStr(haystack1, needle1) == -1);
    CHECK(soln.strStr(haystack2, needle2) == 9);
    CHECK(soln.strStr(haystack3, needle3) == -1);
    CHECK(soln.strStr(haystack4, needle4) == 0);
    CHECK(soln.strStr(haystack5, needle5) == -1);
    CHECK(soln.strStr(haystack6, needle6) == -1);
}
