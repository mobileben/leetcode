//
// Created by Benjamin Lee on 12/8/22.
// https://leetcode.com/problems/string-to-integer-atoi/
//

/*
 * Legal characters: Digits '0' - '9', ' ', '+', '-', '.'
 *
 * - Remove any leading whitespaces
 * - '-' or '+' will determine positivity or negativity of number. Not clear if there can be more than one in it
 * - Can have leading 0s
 * - Clamp numbers to [-2^31, 2^31 - 1] == [INT_MIN, INT_MAX]
 * - Can use 64-bit numbers internally
 * - Non-digit numbers after starting to read digits is the end
 * - Reaching the end of the string is the end
 *
 * LeetCode solution is a little cleaner in the early ingestion before the digits. I will leave my code this way as
 * the descriptions are slighty vague (to me).
 *
 * I certainly could ingest parts and not have a for loop with all the additional ifs, which would help performance.
 * However, when I ran, it was 100% (0ms) for runtime :)
 *
 * Basically this would be
 * 1. Ingest whitespace
 * 2. Ingest sign
 * 3. Ingest digits
 *
 * If whitespace or signs are omitted, then indices are not moved. Digits also reject everything not a digit.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

class Solution {
public:
    int myAtoi(std::string s) {
        int num = 0;
        int sign = 1;
        bool inDigits = false;
        bool needsDigits = false;
        for (auto ch : s) {
            int digit = ch - '0';
            if (!inDigits) {
                if (digit >= 0 && digit <= 9) {
                    num = digit * sign;
                    inDigits = true;
                } else if (!needsDigits) {
                    if (ch == ' ') {
                        // Swallow
                    } else if (ch == '-') {
                        sign = -1;
                        needsDigits = true;
                    } else if (ch == '+') {
                        needsDigits = true;
                    } else {
                        return 0;
                    }
                } else {
                    return 0;
                }
            } else {
                if (digit >= 0 && digit <= 9) {
                    digit *= sign;
                    if (num > INT_MAX / 10 || (num == INT_MAX / 10 && digit > 7)) {
                        return INT_MAX;
                    } else if (num < INT_MIN/ 10 || (num == INT_MIN / 10 && digit < -8)) {
                        return INT_MIN;
                    }
                    num = num * 10 + digit;
                } else {
                    break;
                }
            }
        }

        return num;
    }
};

TEST_CASE("StringToInteger", "algorithm") {
    Solution soln;
    std::string testCase0 = "";
    std::string testCase1 = "   -42";
    std::string testCase2 = "1";
    std::string testCase3 = "01";
    std::string testCase4 = "010";
    std::string testCase5 = " - 42";
    std::string testCase6 = " -+42";
    std::string testCase7 = "  -042";
    std::string testCase8 = "  +42";
    std::string testCase9 = "4193 with words";
    std::string testCase10 = "2147483647";
    std::string testCase11 = "-2147483648";
    std::string testCase12 = "2147483648";
    std::string testCase13 = "-2147483649";
    std::string testCase14 = "20000000000000000000";

    auto actual0 = soln.myAtoi(testCase0);
    auto actual1 = soln.myAtoi(testCase1);
    auto actual2 = soln.myAtoi(testCase2);
    auto actual3 = soln.myAtoi(testCase3);
    auto actual4 = soln.myAtoi(testCase4);
    auto actual5 = soln.myAtoi(testCase5);
    auto actual6 = soln.myAtoi(testCase6);
    auto actual7 = soln.myAtoi(testCase7);
    auto actual8 = soln.myAtoi(testCase8);
    auto actual9 = soln.myAtoi(testCase9);
    auto actual10 = soln.myAtoi(testCase10);
    auto actual11 = soln.myAtoi(testCase11);
    auto actual12 = soln.myAtoi(testCase12);
    auto actual13 = soln.myAtoi(testCase13);
    auto actual14 = soln.myAtoi(testCase14);

    CHECK(actual0 == 0);
    CHECK(actual1 == -42);
    CHECK(actual2 == 1);
    CHECK(actual3 == 1);
    CHECK(actual4 == 10);
    CHECK(actual5 == 0);
    CHECK(actual6 == 0);
    CHECK(actual7 == -42);
    CHECK(actual8 == 42);
    CHECK(actual9 == 4193);
    CHECK(actual10 == INT_MAX);
    CHECK(actual11 == INT_MIN);
    CHECK(actual12 == INT_MAX);
    CHECK(actual13 == INT_MIN);
    CHECK(actual14 == INT_MAX);
}

