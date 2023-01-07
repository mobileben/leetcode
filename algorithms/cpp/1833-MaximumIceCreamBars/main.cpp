//
// Created by Benjamin Lee on 1/5/23.
// https://leetcode.com/problems/maximum-ice-cream-bars/
// Medium
// Topics
//

/*
 * If we sort, we can then iterate through the sorted array, subtracting the costs.
 *
 * Time Complexity: O(nlogn)
 * Space Complexity: O(logn), for sorting
 *
 * Another way which is more optimal would be to count frequencies of the number of instances of
 * a given cost. This would be stored in an array
 *
 * Time Complexity: O(n + m), where n is the size of the costs array and m is the max cost
 * Space Complexity: O(m)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

class Solution {
public:
#ifdef BRUTE
    int maxIceCream(std::vector<int>& costs, int coins) {
        int count = 0;
        std::sort(costs.begin(), costs.end());

        for (auto cost : costs) {
            coins -= cost;
            if (coins >= 0) {
                ++count;
            } else {
                break;
            }
        }

        return count;
    }
#else
    int maxIceCream(std::vector<int>& costs, int coins) {
        int size = costs.size();
        int max = *std::max_element(costs.begin(), costs.end());
        std::vector<int> frequencies(max+1);
        int count = 0;

        for (auto cost : costs) {
            frequencies[cost]++;
        }

        for (int cost=1;cost <= max;++cost) {
            if (frequencies[cost] == 0) continue;

            if (coins < cost) {
                break;
            }

            int t = std::min(frequencies[cost], coins / cost);
            coins -= cost * t;
            count += t;
        }

        return count;
    }
#endif /* BRUTE */
};

TEST_CASE("MaximumIceCreamBars", "algorithm") {
    Solution soln;
    std::vector<int> testCase0{1};
    std::vector<int> testCase1{1};
    std::vector<int> testCase2{2, 1};
    std::vector<int> testCase3{2, 1};
    std::vector<int> testCase4{1, 3, 2, 4, 1};
    std::vector<int> testCase5{10, 6, 8, 7, 7, 8};
    std::vector<int> testCase6{1, 6, 3, 1, 2, 5};

    CHECK(soln.maxIceCream(testCase0, 1) == 1);
    CHECK(soln.maxIceCream(testCase1, 1) == 1);
    CHECK(soln.maxIceCream(testCase2, 1) == 1);
    CHECK(soln.maxIceCream(testCase3, 3) == 2);
    CHECK(soln.maxIceCream(testCase4, 7) == 4);
    CHECK(soln.maxIceCream(testCase5, 5) == 0);
    CHECK(soln.maxIceCream(testCase6, 20) == 6);
}
