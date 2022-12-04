//
// Created by Benjamin Lee on 12/2/22.
// https://leetcode.com/problems/roman-to-integer/
//

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

class Solution {
public:
    static const int NUM_SYMBOLS = 7;
    char symbols[NUM_SYMBOLS] = { 'I', 'V', 'X', 'L', 'C', 'D', 'M' };
    int values[NUM_SYMBOLS] = { 1, 5, 10, 50, 100, 500, 1000 };

    int romanToInt(std::string s) {
        int value = 0;

        int lastIndex = -1;
        for (int i=s.length() - 1;i >= 0;--i) {
            // We are guaranteed that the char values are in the symbols set
            int index = 0;
            auto ch = s.at(i);
            for (auto j=0;j<NUM_SYMBOLS;++j) {
                if (symbols[j] == ch) {
                    index = j;
                    break;
                }
            }
            if (lastIndex > index) {
                value -= values[index];
            } else {
                value += values[index];
            }
            lastIndex = index;
        }

        return value;
    }
};

TEST_CASE("RomanToInteger", "algorithm") {
    Solution soln;
    auto testCase0 = "I";
    auto testCase1 = "II";
    auto testCase2 = "IV";
    auto testCase3 = "V";
    auto testCase4 = "VI";
    auto testCase5 = "VII";
    auto testCase6 = "IX";
    auto testCase7 = "X";
    auto testCase8 = "XI";
    auto testCase9 = "XIV";
    auto testCase10 = "XXXIV";
    auto testCase11 = "XL";
    auto testCase12 = "LXI";
    auto testCase13 = "XC";

    CHECK(soln.romanToInt(testCase0) == 1);
    CHECK(soln.romanToInt(testCase1) == 2);
    CHECK(soln.romanToInt(testCase2) == 4);
    CHECK(soln.romanToInt(testCase3) == 5);
    CHECK(soln.romanToInt(testCase4) == 6);
    CHECK(soln.romanToInt(testCase5) == 7);
    CHECK(soln.romanToInt(testCase6) == 9);
    CHECK(soln.romanToInt(testCase7) == 10);
    CHECK(soln.romanToInt(testCase8) == 11);
    CHECK(soln.romanToInt(testCase9) == 14);
    CHECK(soln.romanToInt(testCase10) == 34);
    CHECK(soln.romanToInt(testCase11) == 40);
    CHECK(soln.romanToInt(testCase12) == 61);
    CHECK(soln.romanToInt(testCase13) == 90);
}