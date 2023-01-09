//
// Created by Benjamin Lee on 1/8/23.
// https://leetcode.com/problems/permutations/
// Medium
// Topics: Array, Backtracking
//

/*
 * The easy way to do this is to use std::next_permutation.
 *
 * The other way to approach this is through backtracking. With backtracking, we take some action and then discard this
 * to be able to apply the action again with another permutation. In this case, we use a swap. And we undo this swap after
 * we permute.
 *
 * Time Complexity: Approx O(n!) (slighly slower than)
 * Space Complexity: O(n!)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

class Solution {
public:
#ifdef STD
    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        std::vector<std::vector<int>> results;
        std::sort(nums.begin(), nums.end());
        do {
            results.push_back(nums);
        } while(std::next_permutation(nums.begin(), nums.end()));

        return results;
    }
#else
    void permute(std::vector<int>& nums, std::vector<std::vector<int>>& output, int first) {
        if (first == nums.size()) {
            output.push_back(nums);
        }

        for (int i=first;i<nums.size();++i) {
            std::iter_swap(nums.begin() + first, nums.begin() + i);
            permute(nums, output, first + 1);
            std::iter_swap(nums.begin() + first, nums.begin() + i);
        }
    }

    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        std::vector<std::vector<int>> results;

        permute(nums, results, 0);

        return results;
    }
#endif /* STD */
};

bool operator==(const std::vector<std::vector<int>>& lhs, const std::vector<std::vector<int>>& rhs) {
    std::set<std::vector<int>> lset;
    std::set<std::vector<int>> rset;

    for (auto& l : lhs) {
        lset.insert(l);
    }

    for (auto& r : rhs) {
        rset.insert(r);
    }

    return lset == rset;
}

TEST_CASE("Permutations", "algorithm") {
    Solution soln;
    std::vector<int> testCase0{1, 2, 3};
    std::vector<int> testCase1{0, 1};
    std::vector<int> testCase2{1};
    std::vector<int> testCase3{1, 2, 3};
    std::vector<int> testCase4{0, -1, 2};

    std::vector<std::vector<int>> expected0{{1, 2, 3},{1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}};
    std::vector<std::vector<int>> expected1{{0, 1}, {1, 0}};
    std::vector<std::vector<int>> expected2{{1}};
    std::vector<std::vector<int>> expected3{{1,2,3,4},{1,2,4,3},{1,3,2,4},{1,3,4,2},{1,4,2,3},{1,4,3,2},{2,1,3,4},{2,1,4,3},{2,3,1,4},{2,3,4,1},{2,4,1,3},{2,4,3,1},{3,1,2,4},{3,1,4,2},{3,2,1,4},{3,2,4,1},{3,4,1,2},{3,4,2,1},{4,1,2,3},{4,1,3,2},{4,2,1,3},{4,2,3,1},{4,3,1,2},{4,3,2,1}};
    std::vector<std::vector<int>> expected4{{-1, 0, 1}, {-1, 1, 0}, {0, -1, 1}, {0, 1, -1}, {1, -1, 0}, {1, 0, -1}};

    auto results0 = soln.permute(testCase0) == expected0;
    auto results1 = soln.permute(testCase1) == expected1;
    auto results2 = soln.permute(testCase2) == expected2;
    auto results3 = soln.permute(testCase3) == expected3;
    auto results4 = soln.permute(testCase4) == expected4;

    CHECK(results0);
    CHECK(results1);
    CHECK(results2);
    CHECK(results3);
    CHECK(results4);
}