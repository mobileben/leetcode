//
// Created by Benjamin Lee on 12/5/22.
// https://leetcode.com/problems/add-binary/
//

/*
 * This is similar to 66 Plus One, but on a binary level. However, where Plus One dealt with incrementing a number
 * represented by a vector of ints, this adds two different binary numbers represented by a string.
 * Some key elements here
 * - a and b can be of different lengths
 * - a and b consist of only '0' and '1'
 *
 * Time Complexity: O(max(n, m))
 * Space Complexity: O(max(n, m))
 *
 * This also can be done using bitwise operators. Apparently FB asks a variation of this, but doesn't allow add.
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

class Solution {
public:
    std::string addBinary(std::string a, std::string b) {
        auto& l = a.length() > b.length() ? a : b;
        auto& r = a.length() > b.length() ? b : a;

        int lIndex = l.length() - 1;
        int rIndex = r.length() - 1;

        int sum, carry = 0;
        int lNum, rNum;
        for (int i=lIndex;i>=0;--i) {
            lNum = l[i] - '0';
            rNum = (rIndex >= 0 ? r[rIndex--] : '0') - '0';

            sum = lNum + rNum + carry;
            carry = sum > 1 ? 1 : 0;
            if (carry) {
                // Note this could be done with modulo instead (eg. sum % 2)
                l[i] = sum == 2 ? '0' : '1';
            } else {
                l[i] = sum + '0';
            }
        }
        if (carry) {
            l.insert(l.begin(), '1');
        }

        return l;
    }
};

TEST_CASE("AddBinary", "algorithm") {
    Solution soln;
    std::string testCaseA0 = "0";
    std::string testCaseB0 = "0";
    std::string testCaseA1 = "0";
    std::string testCaseB1 = "1";
    std::string testCaseA2 = "1";
    std::string testCaseB2 = "0";
    std::string testCaseA3 = "1";
    std::string testCaseB3 = "10";
    std::string testCaseA4 = "1";
    std::string testCaseB4 = "11";
    std::string testCaseA5 = "10";
    std::string testCaseB5 = "1";
    std::string testCaseA6 = "11";
    std::string testCaseB6 = "1";
    std::string testCaseA7 = "1010";
    std::string testCaseB7 = "1011";
    std::string testCaseA8 = "1011";
    std::string testCaseB8 = "1010";
    std::string testCaseA9 = "10";
    std::string testCaseB9 = "11";

    std::string expected0 = "0";
    std::string expected1 = "1";
    std::string expected2 = "1";
    std::string expected3 = "11";
    std::string expected4 = "100";
    std::string expected5 = "11";
    std::string expected6 = "100";
    std::string expected7 = "10101";
    std::string expected8 = "10101";
    std::string expected9 = "101";

    CHECK(soln.addBinary(testCaseA0, testCaseB0) == expected0);
    CHECK(soln.addBinary(testCaseA1, testCaseB1) == expected1);
    CHECK(soln.addBinary(testCaseA2, testCaseB2) == expected2);
    CHECK(soln.addBinary(testCaseA3, testCaseB3) == expected3);
    CHECK(soln.addBinary(testCaseA4, testCaseB4) == expected4);
    CHECK(soln.addBinary(testCaseA5, testCaseB5) == expected5);
    CHECK(soln.addBinary(testCaseA6, testCaseB6) == expected6);
    CHECK(soln.addBinary(testCaseA7, testCaseB7) == expected7);
    CHECK(soln.addBinary(testCaseA8, testCaseB8) == expected8);
    CHECK(soln.addBinary(testCaseA9, testCaseB9) == expected9);
}

