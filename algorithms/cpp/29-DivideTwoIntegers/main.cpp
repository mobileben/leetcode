//
// Created by Benjamin Lee on 12/12/22.
// https://leetcode.com/problems/divide-two-integers/
//

/*
 *
 * We are not allowed to use multiplication, division, or mod.
 *
 * The easiest way to do this is to
 * - Trivially reject dividend == INT_MIN and divisor == -1, as this will overflow
 * - Determine the resulting sign
 * - Convert dividend and divisor to negative numbers, since negative numbers have more range
 *
 * We also have to adhere to the rule of if the quotient is strictly greater than INT_MAX (2^31 - 1), then return INT_MAX
 * and if quotient is strictly less then -2^31, then return -2^31 (INT_MIN)
 *
 * This is slow and will often TLE
 *
 * Time Complexity: O(n) where n is the abs of the dividend (worse case when divisor == 1)
 * Space Complexity: O(1)
 *
 * If we repeatedly double our divisor, we can more quickly converge to the dividend. We will hit a point where we exceed
 * the dividend. And when this happens, we need to single step through the difference between the excess and the last
 * good value. Or looking at it another way, pre-compute when we will exceed the bounds, so we can stop the doubling
 * process before hand. Keep in mind this doubling is 2^n, where n is the number of steps we use for doubling.
 *
 * Time Complexity: O(log^2n)
 * Space Complexity: O(n)
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

class Solution {
public:
#ifdef BRUTE
    int divide(int dividend, int divisor) {
        if (dividend == INT_MIN && divisor == -1) return INT_MAX;

        bool negative = (dividend < 0) ^ (divisor < 0);
        // We convert to negative numbers since negative numbers have the largest range
        // INT_MAX is 2^31 whereas INT_MIN is 2^31 - 1
        if (dividend > 0) {
            dividend = -dividend;
        }
        if (divisor > 0) {
            divisor = -divisor;
        }

        if (divisor == -1) {
            return negative ? dividend : -dividend;
        }

        int quotient = 0;
        while (dividend <= divisor) {
            dividend -= divisor;
            --quotient;
        }

        if (!negative) {
            quotient = -quotient;
        }
        return quotient;
    }
#else
    int divide(int dividend, int divisor) {
        if (dividend == INT_MIN && divisor == -1) return INT_MAX;

        bool negative = (dividend < 0) ^ (divisor < 0);
        // We convert to negative numbers since negative numbers have the largest range
        // INT_MAX is 2^31 whereas INT_MIN is 2^31 - 1
        if (dividend > 0) {
            dividend = -dividend;
        }
        if (divisor > 0) {
            divisor = -divisor;
        }

        if (divisor == -1) {
            return negative ? dividend : -dividend;
        }

        int quotient = 0;
        while (dividend <= divisor) {
            int pow2 = -1;
            int value = divisor;

            // Use half of INT_MIN because if we double that, we'll overflow
            while (value >= INT_MIN / 2 && dividend <= (value + value)) {
                value += value;
                pow2 += pow2;
            }

            dividend -= value;
            quotient += pow2;
        }

        if (!negative) {
            quotient = -quotient;
        }
        return quotient;
    }
#endif /* BRUTE */
};

TEST_CASE("DivideTwoIntegers", "algorithm") {
    Solution soln;
    int dividend0 = 0;
    int divisor0 = 1;
    int dividend1 = 0;
    int divisor1 = -1;
    int dividend2 = 8;
    int divisor2 = 2;
    int dividend3 = -8;
    int divisor3 = 2;
    int dividend4 = 8;
    int divisor4 = -2;
    int dividend5 = -8;
    int divisor5 = -2;
    int dividend6 = 10;
    int divisor6 = 3;
    int dividend7 = 7;
    int divisor7 = -3;
    int dividend8 = -2147483648;
    int divisor8 = -1;
    int dividend9 = -1;
    int divisor9 = -1;
    int dividend10 = -2147483648;
    int divisor10 = 2;

    CHECK(soln.divide(dividend0, divisor0) == 0);
    CHECK(soln.divide(dividend1, divisor1) == 0);
    CHECK(soln.divide(dividend2, divisor2) == 4);
    CHECK(soln.divide(dividend3, divisor3) == -4);
    CHECK(soln.divide(dividend4, divisor4) == -4);
    CHECK(soln.divide(dividend5, divisor5) == 4);
    CHECK(soln.divide(dividend6, divisor6) == 3);
    CHECK(soln.divide(dividend7, divisor7) == -2);
    CHECK(soln.divide(dividend8, divisor8) == 2147483647);
    CHECK(soln.divide(dividend9, divisor9) == 1);
    CHECK(soln.divide(dividend10, divisor10) == -1073741824);
}

