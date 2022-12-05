//
// Created by Benjamin Lee on 12/5/22.
// https://leetcode.com/problems/length-of-last-word/
//

/*
 *
 *  The basics of solving this are detecting when we are in a word and counting it. It is important to factor in that
 *  we can have a trailing space.
 *
 *  A naive approach would be to go left to right, counting each word.
 *
 *  However, a better approach is going right to left, stopping when the word ends.
 *
 *  Both are
 *  Time Complexity: O(n)
 *  Space Complexity: O(1)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

class Solution {
public:
#ifdef NAIVE
    int lengthOfLastWord(std::string s) {
        char last = ' ';
        int lastWord = 0;
        int wordLen = 0;

        for (auto ch : s) {
            if (ch != ' ') {
                ++wordLen;
            } else {
                if (wordLen) {
                    lastWord = wordLen;
                }
                wordLen = 0;
            }
            last = ch;
        }

        // Handle last word
        if (last != ' ') {
            lastWord = wordLen;
        }

        return lastWord;
    }
#else
    int lengthOfLastWord(std::string s) {
        int wordLen = 0;
        for (int i = s.length() - 1;i>=0;--i) {
            auto ch = s[i];
            if (ch != ' ') {
                ++wordLen;
            } else if (wordLen){
                break;
            }
        }
        return wordLen;
    }
#endif /* NAIVE */
};

TEST_CASE("LengthOfLastWord", "algorithm") {
    Solution soln;
    std::string testCase0{"a"};
    std::string testCase1{" a"};
    std::string testCase2{"a "};
    std::string testCase3{" a "};
    std::string testCase4{"Hello World"};
    std::string testCase5{"  fly me  to  the moon  "};
    std::string testCase6{"luffy is still joyboy"};
    std::string testCase7{"  going     to    the      storefront"};
    std::string testCase8{" a b c d"};
    std::string testCase9{"Today is a nice day"};

    CHECK(soln.lengthOfLastWord(testCase0) == 1);
    CHECK(soln.lengthOfLastWord(testCase1) == 1);
    CHECK(soln.lengthOfLastWord(testCase2) == 1);
    CHECK(soln.lengthOfLastWord(testCase3) == 1);
    CHECK(soln.lengthOfLastWord(testCase4) == 5);
    CHECK(soln.lengthOfLastWord(testCase5) == 4);
    CHECK(soln.lengthOfLastWord(testCase6) == 6);
    CHECK(soln.lengthOfLastWord(testCase7) == 10);
    CHECK(soln.lengthOfLastWord(testCase8) == 1);
    CHECK(soln.lengthOfLastWord(testCase9) == 3);
}