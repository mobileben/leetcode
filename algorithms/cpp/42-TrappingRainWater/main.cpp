//
// Created by Benjamin Lee on 1/4/23.
// https://leetcode.com/problems/trapping-rain-water/
// Hard
// Topics: Array, Two Pointers, Dynamic Programming, Stack, Monotonic Stack
//

/*
 * We can generally observe that trapped water is dependent upon the min height of the max height
 * on both sides minus its height.
 *
 * For the brute force method, for each slice, we can search for the left max and the right max
 * and then find the min of the maximums and add it.
 *
 * Time Complexity: O(n^2), will TLE
 * Space Complexity: O(1)
 *
 * Dynamic programming can be used based on our brute force algorithm. The brute force method, for
 * each slice, checks everything to the left and everything to the right. We can actually find the max
 * values for the left and right ahead of time.
 *
 * Time Complexity: O(n), O(n) + O(n) + O(n)
 * Space Complexity: O(n), O(n) + O(n)
 *
 * One can also use a stack.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#define STACK

#include <stack>

class Solution {
public:
#ifdef BRUTE
    int trap(std::vector<int>& height) {
        // Trivial rejection
        if (height.empty()) return 0;

        int area = 0;
        int size = height.size();
        for(int i=1;i<size - 1;++i) {
            int lmax = 0, rmax = 0;
            for (int j = i; j >= 0; --j) {
                lmax = std::max(lmax, height[j]);
            }
            for (int j = i; j < size; ++j) {
                rmax = std::max(rmax, height[j]);
            }
            area += std::min(lmax, rmax) - height[i];
        }
        return area;
    }
#elifdef DP
    int trap(std::vector<int>& height) {
        // Trivial rejection
        if (height.empty()) return 0;

        int area = 0;
        int size = height.size();
        std::vector<int> lmax(size);
        std::vector<int> rmax(size);

        lmax[0] = height[0];
        for (int i=1;i<size;++i) {
            lmax[i] = std::max(lmax[i-1], height[i]);
        }

        rmax[size-1] = height[size-1];
        for (int i=size-2;i>=0;--i) {
            rmax[i] = std::max(rmax[i + 1], height[i]);
        }

        for (int i=1;i<size - 1;++i) {
            area += std::min(lmax[i], rmax[i]) - height[i];
        }

        return area;
    }
#elifdef STACK
    int trap(std::vector<int>& height) {
        if (height.size() <= 1) {
            return 0;
        }

        int area = 0;
        int curr = 0;
        std::stack<int> stack;

        while (curr < height.size()) {
            // While we have something on our stack and
            while (stack.size() and height[curr] > height[stack.top()]) {
                auto top = stack.top();
                stack.pop();

                if (stack.empty()) break;

                auto prevTop = stack.top();
                int len = curr - prevTop - 1;
                int h = std::min(height[curr], height[prevTop]) - height[top];
                area += len * h;
            }
            stack.push(curr++);
        }

        return area;
    }
#endif /* BRUTE */
};

TEST_CASE("TrappingRainWater", "algorithm") {
    Solution soln;
    std::vector<int> testCase0{1};
    std::vector<int> testCase1{0, 1, 0};
    std::vector<int> testCase2{1, 0, 1};
    std::vector<int> testCase3{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    std::vector<int> testCase4{4, 2, 0, 3, 2, 5};
    std::vector<int> testCase5{0, 1, 2, 0};
    std::vector<int> testCase6{0, 1, 2, 1, 0};
    std::vector<int> testCase7{0, 1, 2, 1, 2};

    CHECK(soln.trap(testCase0) == 0);
    CHECK(soln.trap(testCase1) == 0);
    CHECK(soln.trap(testCase2) == 1);
    CHECK(soln.trap(testCase3) == 6);
    CHECK(soln.trap(testCase4) == 9);
    CHECK(soln.trap(testCase5) == 0);
    CHECK(soln.trap(testCase6) == 0);
    CHECK(soln.trap(testCase7) == 1);
}
