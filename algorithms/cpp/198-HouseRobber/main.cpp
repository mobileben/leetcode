//
// Created by Benjamin Lee on 12/13/22.
// https://leetcode.com/problems/house-robber/
//

/*
 * Brute force for this is a bit painful, because if one exhaustively searches overall permutations, it is every
 * combo of index + 2 or higher, where index is the current item.
 * For example if we have
 * index | 0 1 2 3
 * value | 1 2 3 1
 *
 * Our index combos are
 * 0
 * 0 + 2
 * 1
 * 1 + 3
 * 2
 * 3
 *
 * Another example
 * index | 0 1 2 3 4
 * value | 2 7 9 3 1
 *
 * Our index combos are
 * 0
 * 0 + 2
 * 0 + 2 + 4
 * 0 + 3
 * 0 + 4
 * 1
 * 1 + 3
 * 1 + 4
 * 2
 * 2 + 4
 * 3
 * 4
 *
 * Another example
 * index | 0 1 2 3  4 5
 * value | 7 6 9 11 3 5
 *
 * Our index combos are
 * 0
 * 0 + 2
 * 0 + 2 + 4
 * 0 + 2 + 5
 * 0 + 3
 * 0 + 3 + 5
 * 0 + 4
 * 0 + 5
 * 1
 * 1 + 3
 * 1 + 3 + 5
 * 1 + 4
 * 1 + 5
 * 2
 * 2 + 4
 * 2 + 5
 * 3
 * 3 + 5
 * 4
 * 5
 *
 * What we can observe is that for a given index, we should find the max value of all contributing elements going to it
 * Using example 2, we can see that index for can be involved in several equations
 * 0 + 2 + 4
 * 0 + 4
 * 1 + 4
 * 2 + 4
 * 4
 *
 * If the value at index 4 is the max of these 4 combination, we would get the max value. This could be applied to any
 * of the indices, since each index must satisfy the adjacency rule
 *
 * Time Complexity: O(n^2). This is really n * (n - 2)
 * Space Complexity: O(n)
 *
 * We can do this in a single pass with tabulation (dynamic programming). We work in reverse,
 * For each step, we check to see if we should rob the house, or go the next house. If we rob the current house, we
 * would have nums[curr] + dp[curr + 2] (remember we are going in reverse).
 * As we step along backwards, we compare if we earn more by keeping what we have or robbing the current house.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

class Solution {
public:
#ifdef BRUTE
    int rob(std::vector<int>& nums) {
        // Trivial rejection
        if (nums.size() == 1) return nums.front();
        if (nums.size() == 2) return std::max(nums[0], nums[1]);

        int max = 0;
        std::vector<int> dp(nums.size());

        // Prime first two. They are adjacent
        dp[0] = nums[0];
        dp[1] = nums[1];

        max = std::max(nums[0], nums[1]);

        for (int i=0;i<nums.size();++i) {
            for (int j=i+1;j<nums.size();++j) {
                // Only adjacent count
                if (j > i + 1) {
                    dp[j] = std::max(dp[j], dp[i] + nums[j]);
                    if (dp[j] > max) {
                        max = dp[j];
                    }
                }
            }

        }

        return max;
    }
#else
    int rob(std::vector<int>& nums) {
        // Trivial rejection
        if (nums.size() == 1) return nums.front();
        if (nums.size() == 2) return std::max(nums[0], nums[1]);

        std::vector<int> dp(nums.size() + 1);

        dp[nums.size() - 1] = nums.back();

        for (int i=nums.size() - 2;i>=0;--i) {
            dp[i] = std::max(dp[i+1], dp[i+2] + nums[i]);
        }

        return dp[0];
    }
#endif /* BRUTE */
};

TEST_CASE("HouseRobber", "algorithm") {
    Solution soln;
    std::vector<int> testCase0{1, 2, 3, 1};
    std::vector<int> testCase1{2, 7, 9, 3, 1};
    std::vector<int> testCase2{7, 6, 9, 11, 3, 5};
    std::vector<int> testCase3{1, 3, 1};

    CHECK(soln.rob(testCase2) == 23);   // 7 + 11 + 5
    CHECK(soln.rob(testCase0) == 4);    // 1 + 3
    CHECK(soln.rob(testCase1) == 12);   // 2 + 9 + 1
    CHECK(soln.rob(testCase3) == 3);   // 7 + 11 + 5
}

