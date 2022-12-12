//
// Created by Benjamin Lee on 12/11/22.
// https://leetcode.com/problems/climbing-stairs/
//

/*
 * One can use backtracking to solve this, however this will result in a TLE.
 *
 * Memoization is one way to solve this
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * Dynamic Programming is another way to address this
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * One may notice this is actually a Fibonacci series. This will be similar to DP but with a smaller Space Complexity
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 *
 */
#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>


class Solution {
public:
#ifdef BRUTE
    void backtrack(int steps, int n, int& total) {
        if (steps == n) {
            ++total;
            return;
        }

        if (steps < n) {
            backtrack(steps + 1, n, total);
        }

        if (steps < (n - 1)) {
            backtrack(steps + 2, n, total);
        }
    }

    int climbStairs(int n) {
        int total = 0;
        backtrack(0, n, total);
        return total;
    }
#elif defined(MEMOIZATION)
    int memoize(int steps, int n, std::vector<int>& memo) {
        if (steps > n) {
            return 0;
        }
        if (steps == n) {
            return 1;
        }

        if (memo[steps] > 0) {
            return memo[steps];
        }

        memo[steps] = memoize(steps + 1, n, memo) + memoize(steps + 2, n, memo);
        return memo[steps];
    }

    int climbStairs(int n) {
        std::vector<int> memo(n+1);
        return memoize(0, n, memo);
    }
#elif defined(DP)
    int climbStairs(int n) {
        // Trivial rejection
        if (n == 1) return 1;

        std::vector<int> dp(n);
        dp[0] = 1;
        dp[1] = 2;
        for (int i=2;i<n;i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n-1];
    }
#else
    int climbStairs(int n) {
        // Trivial rejection
        if (n == 1) return 1;

        int first = 1;
        int second = 2;
        for (int i=2;i<n;i++) {
            auto sum = first + second;
            first = second;
            second = sum;
        }
        return second;
    }
#endif /* BRUTE */
};

TEST_CASE("ClimbingStairs", "algorithm") {
    Solution soln;
    int actual0 = soln.climbStairs(1);
    int actual1 = soln.climbStairs(2);
    int actual2 = soln.climbStairs(3);
    int actual3 = soln.climbStairs(4);
    int actual4 = soln.climbStairs(5);

    int expected0 = 1;
    int expected1 = 2;
    int expected2 = 3;
    int expected3 = 5;
    int expected4 = 8;

    CHECK(actual0 == expected0);
    CHECK(actual1 == expected1);
    CHECK(actual2 == expected2);
    CHECK(actual3 == expected3);
    CHECK(actual4 == expected4);
}

