//
// Created by Benjamin Lee on 12/2/22.
// https://leetcode.com/problems/palindrome-number/
//

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

class Solution {
public:
    // Time Complexity: O(log10(n)) since we divide by 10 each iteration
    // Space Complexity: O(1)
    bool isPalindrome(int x) {
        if (x < 0 || (x != 0 and x % 10 == 0)) {
            // Trivial rejection of negative and numbers ending in 0 (since we can't have leading 0s)
            return false;
        }

        int sum = 0;
        int temp = x;
        while (temp > 0) {
            // 10 needs to cast as unsigned, else will get an integer overflow
            sum = sum * 10u + temp % 10;
            temp /= 10;

            // Note we can do better, based on the offical solution by reconstructing the number
            /*
             * int revertedNumber = 0;
             * while(x > revertedNumber) {
             *     revertedNumber = revertedNumber * 10 + x % 10;
             *     x /= 10;
             * }
             *
             * However in this case, the result can either be x == revertedNumber or x == revertedNumber / 10,
             * when number length has an odd number
             */
        }
        return sum == x;
    }
};

TEST_CASE("PalindromeNumber", "algorithm") {
    Solution soln;
    int testCase0 = 0;
    int testCase1 = -1;
    int testCase2 = 1;
    int testCase3 = 11;
    int testCase4 = 12;
    int testCase5 = 121;
    int testCase6 = 123;
    int testCase7 = 1221;
    int testCase8 = 1231;
    int testCase9 = 12221;
    int testCase10 = 12321;
    int testCase11 = 123210;
    int testCase12 = 1234567899; // This will fail on LeetCode, but works fine on my machine

    CHECK(soln.isPalindrome(testCase0) == true);
    CHECK(soln.isPalindrome(testCase1) == false);
    CHECK(soln.isPalindrome(testCase2) == true);
    CHECK(soln.isPalindrome(testCase3) == true);
    CHECK(soln.isPalindrome(testCase4) == false);
    CHECK(soln.isPalindrome(testCase5) == true);
    CHECK(soln.isPalindrome(testCase6) == false);
    CHECK(soln.isPalindrome(testCase7) == true);
    CHECK(soln.isPalindrome(testCase8) == false);
    CHECK(soln.isPalindrome(testCase9) == true);
    CHECK(soln.isPalindrome(testCase10) == true);
    CHECK(soln.isPalindrome(testCase11) == false);
    CHECK(soln.isPalindrome(testCase12) == false);
}