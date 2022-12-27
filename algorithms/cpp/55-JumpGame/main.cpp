//
// Created by Benjamin Lee on 12/26/22.
// https://leetcode.com/problems/jump-game/
//

/*
 * This is a dynamic programming problem. We can work backwards, stepping backwards to see if or our possible jumps
 * that our intended jump location is good. We only need one of the options to be good in order to advance
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n)
 *
 * This can be further optimized down by observing when we are working backwards, we are just determiming if we we
 * have a good jump by checking to see if one of our possible jumps for a spot is valid. We know this is the case
 * as along as our max jump is less than our last position (which will be the left-most position).
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>


class Solution {
public:
#ifdef DP_BOTTOM_UP
    bool canJump(std::vector<int>& nums) {
        int len = nums.size();
        std::vector<bool> dp(len);

        dp[len - 1] = true;
        for (int i=len - 2;i>=0;--i) {
            int max = std::min(i + nums[i], len - 1);
            for (int j=i+1;j<=max;++j) {
                if (dp[j]) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[0];
    }
#else
    bool canJump(std::vector<int>& nums) {
        int last = nums.size() - 1;
        for (int i=nums.size() - 1;i>=0;--i) {
            if ((i + nums[i]) >= last) {
                last = i;
            }
        }
        return last == 0;
    }
#endif /* DP_BOTTOM_UP */
};

TEST_CASE("JumpGame", "algorithm") {
    Solution soln;
    std::vector testCase0{2, 3, 1, 1, 4};
    std::vector testCase1{3, 2, 1, 0, 4};

    CHECK(soln.canJump(testCase0) == true);
    CHECK(soln.canJump(testCase1) == false);
}
