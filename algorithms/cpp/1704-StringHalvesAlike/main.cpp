//
// Created by Benjamin Lee on 12/1/22.
// https://leetcode.com/problems/determine-if-string-halves-are-alike/
//

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <string>
#include <set>

class Solution {
public:
    static const int VOWEL_COUNT = 5;
    std::set<char> vowels{'a', 'e', 'i', 'o', 'u'};
    char myVowels[VOWEL_COUNT] = {'a', 'e', 'i', 'o', 'u'};

    bool isVowel(char ch) {
        auto lower = ch >= 'a' ? ch : ch + ('a' - 'A');
        for (auto i=0;i<VOWEL_COUNT;++i) {
            if (myVowels[i] == lower) {
                return true;
            }
        }
        return false;
    }

    bool halvesAreAlike(std::string s) {
        auto len = s.length();
        auto half = len / 2;
        int offset = half + (len & 1);
        int left = 0, right = 0;
        for (auto i=0;i<half;++i) {
            // Check left
            auto lch = s[i];
            if (isVowel(lch)) {
                ++left;
            }
            // Check right
            auto rch = s[offset + i];
            if (isVowel(rch)) {
                ++right;
            }
        }
        return left == right;
    }
};

TEST_CASE("Determine if Strings Halves Are Alike", "algorithm") {
    Solution soln;
    std::string testCase0{"book"};
    std::string testCase1{"textbook"};
    std::string testCase2{"AORroa"};
    std::string testCase3{""};
    std::string testCase4{"aaa"};
    std::string testCase5{"ant"};
    std::string testCase6{"tna"};
    std::string testCase7{"tan"};

    CHECK(soln.halvesAreAlike(testCase2) == true);
    CHECK(soln.halvesAreAlike(testCase6) == false);
    CHECK(soln.halvesAreAlike(testCase0) == true);
    CHECK(soln.halvesAreAlike(testCase1) == false);
    CHECK(soln.halvesAreAlike(testCase2) == true);
    CHECK(soln.halvesAreAlike(testCase3) == true);
    CHECK(soln.halvesAreAlike(testCase4) == true);
    CHECK(soln.halvesAreAlike(testCase5) == false);
    CHECK(soln.halvesAreAlike(testCase6) == false);
    CHECK(soln.halvesAreAlike(testCase7) == true);

}