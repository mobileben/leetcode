//
// Created by Benjamin Lee on 1/7/23.
// https://leetcode.com/problems/max-points-on-a-line/
// Hard
// Topics: Array, HashMap, Math, Geometry
//

/*
 * The approach here is a bit brute force, but it is considered acceptable to LC. One must iterate each
 * point and then compare the lines relative to that point.
 *
 * One can use either the slope or atan2. If using the slope, one must factor in division by zero.
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <map>

class Solution {
public:
    int maxPoints(std::vector<std::vector<int>>& points) {
        if (points.size() <= 1) return points.size();

        int max = 0;
        for (int i=0;i<points.size();++i) {
            std::map<double, int> slopes;
            for (int j=0;j<points.size();++j) {
                if (i == j) continue;

                int dx = points[j][0] - points[i][0];
                int dy = points[j][1] - points[i][1];
                float m;

                // Note one could also use atan2(dy, dx) as well
                if (dx == 0) {
                    // Can't divide by zero, use max value
                    m = static_cast<double>(std::numeric_limits<double>::max());
                } else {
                    m = static_cast<double>(dy) / static_cast<double>(dx);
                }
                slopes[m]++;

            }
            for (auto it : slopes) {
                int count = it.second + 1;
                max = std::max(max, count);
            }
        }

        return max;
    }
};

TEST_CASE("MaxPointsOnLine", "algorithm") {
    Solution soln;
    std::vector<std::vector<int>> testCase0{{1, 1}, {2, 2}, {3, 3}};
    std::vector<std::vector<int>> testCase1{{1, 1}, {3, 2}, {5, 3}, {4, 1}, {2, 3}, {1, 4}};
    std::vector<std::vector<int>> testCase2{{0,0},{4,5},{7,8},{8,9},{5,6},{3,4},{1,1}};
    std::vector<std::vector<int>> testCase3{{4, 0}, {4, 1}, {4, 2}};

    CHECK(soln.maxPoints(testCase2) == 5);
    CHECK(soln.maxPoints(testCase0) == 3);
    CHECK(soln.maxPoints(testCase1) == 4);
    CHECK(soln.maxPoints(testCase3) == 3);
}
