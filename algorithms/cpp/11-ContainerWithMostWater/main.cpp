//
// Created by Benjamin Lee on 12/10/22.
// https://leetcode.com/problems/container-with-most-water/
//

/*
 * Brute force method would be to go through all combinations to find the max area.
 * Brute force will end up with TLE.
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 *
 * Thus we are forced to do this more optimally. We can do this using two pointers, one for left and one for right
 *
 * The farther the lines are apart, the better the chance it area will be greater. We can start outwards and move
 * inwards. But when we move inwards, we want to do it one edge at a time. But which edge do we move? We will want
 * to move the edge that is shorter. This is because as we move inwards, we need a higher edge to offset the loss from
 * the loss in width.
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
    int maxArea(std::vector<int>& height) {
        int max = 0;

        for (int left=0;left<height.size();++left) {
            for (int right=left+1;right<height.size();++right) {
                auto area = (right - left) * std::min(height[left], height[right]);
                if (area > max) {
                    max = area;
                }
            }
        }

        return max;
    }
#else
    int maxArea(std::vector<int>& height) {
        int max = 0;
        int left = 0, right = height.size() - 1;

        while (left < right) {
            auto area = (right - left) * std::min(height[left], height[right]);

            if (area > max) {
                max = area;
            }

            if (height[left] <= height[right]) {
                // Move left because it is the minimum edge that allows for the possibility of increasing the area
                // Due to having a higher edge tou use
                ++left;
            } else {
                --right;
            }
        }

        return max;
    }
#endif /* BRUTE */
};

TEST_CASE("ContainerWithMostWater", "algorithm") {
    Solution soln;
    std::vector<int> testCase0{0, 0};
    std::vector<int> testCase1{0, 1};
    std::vector<int> testCase2{1, 1};
    std::vector<int> testCase3{1, 1, 2, 2, 1, 1};
    std::vector<int> testCase4{1, 8, 6, 2, 5, 4, 8, 3, 7};
    std::vector<int> testCase5{1, 8, 6, 2, 1, 5, 4, 8, 6};

    int actual0 = soln.maxArea(testCase0);
    int actual1 = soln.maxArea(testCase1);
    int actual2 = soln.maxArea(testCase2);
    int actual3 = soln.maxArea(testCase3);
    int actual4 = soln.maxArea(testCase4);
    int actual5 = soln.maxArea(testCase5);

    CHECK(actual0 == 0);
    CHECK(actual1 == 0);
    CHECK(actual2 == 1);
    CHECK(actual3 == 5);
    CHECK(actual4 == 49);
    CHECK(actual5 == 48);
}

