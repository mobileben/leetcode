//
// Created by Benjamin Lee on 1/4/23.
// https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/
// Medium
// Topics: Array, Greedy, Sorting
//

/*
 * We can look at this two ways. Both require sorting. Each one looks at the problem slightly differently.
 *
 * The first case is sorting based on the left edge. If the left edges are equal, the larger right values
 * come first. In this case, we track the rightmost value, and always select the minimum rightmost values
 * when we have a balloon that will be popped.
 *
 * We know we need to jump to the next balloon set when our left most edge is greater than the rightmost
 * edge we are tracking (the min right)
 *
 * Time Complexity: O(nlogn)
 * Space Complexity: O(nlogn), for sorting
 *
 * The second case sorts at the right most edge. In this case, we are simplifying the above logic.
 *
 * Time Complexity: O(nlogn)
 * Space Complexity: O(nlogn), for sorting
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#define BRUTE

class Solution {
public:
#ifdef BRUTE
    int findMinArrowShots(std::vector<std::vector<int>>& points) {
        std::sort(points.begin(), points.end(), [&](const std::vector<int>& lhs, const std::vector<int>& rhs) {
            if (lhs[0] < rhs[0]) {
                return true;
            } else if (lhs[0] == rhs[0]) {
                return lhs[1] > rhs[1];
            } else {
                return false;
            }
        });

        int count = 1;
        int index = 0;  // The balloon we are focusing on with the lowest index 0 value
        int right = points[index][1]; // This will be the min value of the right side for ballons we are going to pop

        for (auto& pt : points) {
            if (pt[0] <= right) {
                // As our list is sorted, we just need to look at the left edge to make sure it is <= right
                right = std::min(right, pt[1]);
            } else {
                // This means that we don't overlap at all, so increment and move on
                right = pt[1];
                ++count;
            }
        }
        return count;
    }
#else
    int findMinArrowShots(std::vector<std::vector<int>>& points) {
        std::sort(points.begin(), points.end(), [](const std::vector<int>& lhs, std::vector<int>& rhs) {
            return lhs[1] < rhs[1];
        });

        int count = 1;
        int right= points[0][1];

        for (auto& pt : points) {
            if (right < pt[0]) {
                ++count;
                right = pt[1];
            }
        }

        return count;
    }
#endif /* BRUTE */
};

TEST_CASE("MinimumNumArrowsToBurstBalloons", "algorithm") {
    Solution soln;
    std::vector<std::vector<int>> testCase0{{1, 2}};
    std::vector<std::vector<int>> testCase1{{10, 16}, {2, 8}, {1, 6}, {7, 12}};
    std::vector<std::vector<int>> testCase2{{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    std::vector<std::vector<int>> testCase3{{1, 2}, {2, 3}, {3, 4}, {4, 5}};
    std::vector<std::vector<int>> testCase4{{1, 6}, {2, 8}, {6, 12}};
    std::vector<std::vector<int>> testCase5{{9,12},{1,10},{4,11},{8,12},{3,9},{6,9},{6,7}};

    CHECK(soln.findMinArrowShots(testCase0) == 1);
    CHECK(soln.findMinArrowShots(testCase1) == 2);
    CHECK(soln.findMinArrowShots(testCase2) == 4);
    CHECK(soln.findMinArrowShots(testCase3) == 2);
    CHECK(soln.findMinArrowShots(testCase4) == 1);
    CHECK(soln.findMinArrowShots(testCase5) == 2);
}
