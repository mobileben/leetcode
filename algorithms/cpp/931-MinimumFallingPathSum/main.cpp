//
// Created by Benjamin Lee on 12/13/22.
// https://leetcode.com/problems/minimum-falling-path-sum/
//

/*
 * When falling we have 3 possible paths downwards:
 * - Lower left (i - 1, j + 1)
 * - Straight down (i, j + 1)
 * - Lower right (i + 1, j + 1)
 *
 * This approach can be considered a depth first search (DFS) aproach.
 *
 * This is very slow and will TLE.
 *
 * Time Complexity: O(n * 3^n)
 * Space Complexity: O(n)
 *
 * A better approach to solving this is to use dynamic programming. This can be done either top down or bottom up.
 * A top down approach would be considered memoization and the bottom up approach would be considered tabulation.
 *
 * Memoization is similar to our BRUTE method, however we are using cached values.
 *
 * My non-brute method uses tabulation but approaches it top down.
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n^2)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

class Solution {
public:
#ifdef BRUTE
    int fallingPathSum(int i, int j, int sum, std::vector<std::vector<int>>& matrix) {
        if (i == (matrix.size() - 1)) {
            return matrix[i][j];
        }
        if (j < 0 || j >= matrix.front().size()) {
            return INT_MAX;
        }

        auto left = fallingPathSum(i + 1, j - 1, sum, matrix);
        auto mid = fallingPathSum(i + 1, j, sum, matrix);
        auto right = fallingPathSum(i + 1, j + 1, sum, matrix);

        return std::min(left, std::min(mid, right)) + matrix[i][j];
    }

    int minFallingPathSum(std::vector<std::vector<int>>& matrix) {
        int min = INT_MAX;
        for (int j=0;j<matrix.size();++j) {
            min = std::min(min, fallingPathSum(0, j, 0, matrix));
        }
        return min;
    }
#else
    int minFallingPathSum(std::vector<std::vector<int>>& matrix) {
        // Could reduce space complexity by using tesing instead of space for the left and right edges.
        std::vector<std::vector<int>> dp(matrix.size(), std::vector<int>(matrix.front().size()+2, INT_MAX));
        int min = INT_MAX;
        int m = matrix.size(), n = matrix.front().size();

        // Fill in top row with matrix values
        for (int j=1;j<=n;++j) {
            dp[0][j] = matrix[0][j-1];
        }
        for (int i=1;i<m;++i) {
            for (int j=1;j<=n;++j) {
                int addend = std::min(std::min(dp[i-1][j-1], dp[i-1][j]), dp[i-1][j+1]);
                dp[i][j] = addend + matrix[i][j-1];
            }
        }

        for (int j=1;j<=n;++j) {
            if (dp[m - 1][j] < min) {
                min = dp[m - 1][j];
            }
        }

        return min;
    }
#endif /* BRUTE */
};

TEST_CASE("MinimumFallingPathSum", "algorithm") {
    Solution soln;
    std::vector<std::vector<int>> testCase0{{2,1,3},{6,5,4},{7,8,9}};
    std::vector<std::vector<int>> testCase1{{-19, 57}, {-40, -5}};
    std::vector<std::vector<int>> testCase2{{-19,-1,-96,48,-94,36,16,55,-42,37,-59,6,-32,96,95,-58,13,-34,94,85},{17,44,36,-29,84,80,-34,50,-99,64,13,91,-27,25,-36,57,20,98,-100,-72},{-92,-75,86,90,-4,90,64,56,50,-63,10,-15,90,-66,-66,32,-69,-78,1,60},{21,51,-47,-43,-14,99,44,90,8,11,99,-62,57,59,69,50,-69,32,85,13},{-28,90,12,-18,23,61,-55,-97,6,89,36,26,26,-1,46,-50,79,-45,89,86},{-85,-10,49,-10,2,62,41,92,-67,85,86,27,89,-50,77,55,22,-82,-94,-98},{-50,53,-23,55,25,-22,76,-93,-7,66,-75,42,-35,-96,-5,4,-92,13,-31,-100},{-62,-78,8,-92,86,69,90,-37,81,97,53,-45,34,19,-19,-39,-88,-75,-74,-4},{29,53,-91,65,-92,11,49,26,90,-31,17,-84,12,63,-60,-48,40,-49,-48,88},{100,-69,80,11,-93,17,28,-94,52,64,-86,30,-9,-53,-8,-68,-33,31,-5,11},{9,64,-31,63,-84,-15,-30,-10,67,2,98,73,-77,-37,-96,47,-97,78,-62,-17},{-88,-38,-22,-90,54,42,-29,67,-85,-90,-29,81,52,35,13,61,-18,-94,61,-62},{-23,-29,-76,-30,-65,23,31,-98,-9,11,75,-1,-84,-90,73,58,72,-48,30,-81},{66,-33,91,-6,-94,82,25,-43,-93,-25,-69,10,-71,-65,85,28,-52,76,25,90},{-3,78,36,-92,-52,-44,-66,-53,-55,76,-7,76,-73,13,-98,86,-99,-22,61,100},{-97,65,2,-93,56,-78,22,56,35,-24,-95,-13,83,-34,-51,-73,2,7,-86,-19},{32,94,-14,-13,-6,-55,-21,29,-21,16,67,100,77,-26,-96,22,-5,-53,-92,-36},{60,93,-79,76,-91,43,-95,-16,74,-21,85,43,21,-68,-32,-18,18,100,-43,1},{87,-31,26,53,26,51,-61,92,-65,17,-41,27,-42,-14,37,-46,46,-31,-74,23},{-67,-14,-20,-85,42,36,56,9,11,-66,-59,-55,5,64,-29,77,47,44,-33,-77}};

    auto actual0 = soln.minFallingPathSum(testCase0);
    auto actual1 = soln.minFallingPathSum(testCase1);
    auto actual2 = soln.minFallingPathSum(testCase2);

    CHECK(actual0 == 13);
    CHECK(actual1 == -59);
    CHECK(actual2 == -1428);
}

