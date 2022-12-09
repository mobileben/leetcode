//
// Created by Benjamin Lee on 12/8/22.
// https://leetcode.com/problems/reverse-integer/
//

/*
 *
 * This key to this is managing the overflow. This problem constrains operations to 32-bit numbers. There are two
 * possible places for overflow.
 * - Updating the multiplication
 * - Updating total based on the digit and multiplier
 * Brute force method you can convert to a string and then loop in each case, applying the updates piecemeal.
 * One can use INT_MIN and increment from there, detecting when we go > 0.
 *
 * Time Complexity: O(log10 x)
 * Space Complexity: O(log10 x) // Since storing in strings
 *
 * Another way to approach this is to use div and mod to reverse the number;
 * The issue I have with this exercise is the customization required to protect against overflow. One must know the
 * actual values of INT_MIN and INT_MAX more specifically that INT_MIN ends in 7 and INT_MAX ends in 8.
 *
 * If one were to extend this to 64-bits, they'd need to make adjustments to the "magic numbers"
 *
 * Time Complexity: O(log10 x)
 * Space Complexity: O(1)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <sstream>
#include <iostream>

class Solution {
public:
#ifdef BRUTE
    int reverse(int x) {
        int negative = x < 0 ? 1 : 0;
        std::string s = std::to_string(x);


        std::reverse(s.begin() + negative, s.end());

        // Our method is to
        int total = 0;
        int multiplier = 1;
        int check = negative ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
        int multiplierCheck = std::numeric_limits<int>::min();

        if (negative) {
            auto end = s.length() - 1;

            for (int i=end;i>=negative;--i) {
                // Also need to safety check multiplier
                int digit = s[i] - '0';
                while (digit-- > 0) {
                    check += multiplier;
                    if (check > 0) {
                        return 0;
                    }
                    total -= multiplier;
                }

                digit = 9;
                if (i > negative) {
                    auto addend = multiplier;
                    while (digit-- > 0) {
                        multiplierCheck += addend;
                        multiplier += addend;
                        if (multiplierCheck > 0) {
                            return 0;
                        }
                    }
                }
            }
        } else {
            auto end = s.length() - 1;
            for (int i=end;i>=negative;--i) {
                int digit = (s[i] - '0');
                while (digit-- > 0) {
                    check -= multiplier;
                    if (check < 0) {
                        return 0;
                    }
                    total += multiplier;

                }
                digit = 9;
                if (i > negative) {
                    auto addend = multiplier;
                    while (digit-- > 0) {
                        multiplierCheck += addend;
                        multiplier += addend;
                        if (multiplierCheck > 0) {
                            return 0;
                        }
                    }
                }
            }
        }

        return total;
    }
#else
    int reverse(int x) {
        int rev= 0;

        while (x != 0) {
            int amount = x % 10; // Last digit
            x /= 10;            // Shift to the right

            // Boundary checks
            // Before we shift and add, verify we are in bounds so as to avoid an overflow

            // Upper bounds check. INT_MAX == 2147483647
            if (rev > INT_MAX / 10 || (rev == INT_MAX / 10 && amount > 7)) return 0;

            // Lower bounds check. INT_MIN == -2147483648.
            if (rev < INT_MIN / 10 || (rev == INT_MIN / 10 && amount < -8)) return 0;

            // Shift to left and add amount
            rev = rev * 10 + amount;
        }

        return rev;
    }
#endif /* BRUTE */
};

TEST_CASE("ReverseInteger", "algorithm") {
   Solution soln;
   int testCase0 = 0;
    int testCase1 = 1;
    int testCase2 = -1;
    int testCase3 = 12;
    int testCase4 = -12;
    int testCase5 = 123;
    int testCase6 = -123;
    int testCase7 = 120;
    int testCase8 = -120;
    int testCase9 = std::numeric_limits<int>::max();    // Will go out of bound
    int testCase10 = std::numeric_limits<int>::min();   // Will go out of bounds
    int testCase11 = std::numeric_limits<int>::max() - 1;    // Will be in bounds, cannot properly test negative reaching INT_MAX
    int testCase12 = 1534236469;
    int testCase13 = -2147483412;
    // 2147483647
    // -2147483648
    int actual12 = soln.reverse(testCase12);
    int actual0 = soln.reverse(testCase0);
    int actual1 = soln.reverse(testCase1);
    int actual2 = soln.reverse(testCase2);
    int actual3 = soln.reverse(testCase3);
    int actual4 = soln.reverse(testCase4);
    int actual5 = soln.reverse(testCase5);
    int actual6 = soln.reverse(testCase6);
    int actual7 = soln.reverse(testCase7);
    int actual8 = soln.reverse(testCase8);
    int actual9 = soln.reverse(testCase9);
    int actual10 = soln.reverse(testCase10);
    int actual11 = soln.reverse(testCase11);
    int actual13 = soln.reverse(testCase13);

    CHECK(actual0 == 0);
    CHECK(actual1 == 1);
    CHECK(actual2 == -1);
    CHECK(actual3 == 21);
    CHECK(actual4 == -21);
    CHECK(actual5 == 321);
    CHECK(actual6 == -321);
    CHECK(actual7 == 21);
    CHECK(actual8 == -21);
    CHECK(actual9 == 0);
    CHECK(actual10 == 0);
    CHECK(actual11 == 0);
    CHECK(actual12 == 0);
    CHECK(actual13 == -2143847412);
}
