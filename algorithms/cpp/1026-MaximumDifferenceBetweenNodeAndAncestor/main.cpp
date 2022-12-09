//
// Created by Benjamin Lee on 12/8/22.
// https://leetcode.com/problems/maximum-difference-between-node-and-ancestor/
//

/*
 * We are presented with 2 constaints for node a being an ancestor of b
 * - Any child of a is equal to b
 * - Any child of a is an ancestor of b
 *
 * This description is not great.
 *
 * In my brute force method I use recursive DFS and another stack to track the values to check against. This will be slow.
 *
 * Time Complexity: O(n^2), since it is possible comparison stack is n long
 * Space Complexity: O(2n) => O(n), for recursion and stack
 *
 * A better approach is to use recursive DFS, but to pass down the min/max values along the way, so the largest diff
 * can be calculated.
 *
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "../include/BinarySearchTree.h"

#include <stack>

class Solution {
public:
#ifdef BRUTE
    std::vector<int> values;
    int max = INT_MIN;

    void dfs(TreeNode *root) {
        if (!root) return;

        for (auto val : values) {
            auto diff = std::abs(val - root->val);
            if (diff > max) {
                max = diff;
            }
        }
        values.push_back(root->val);

        dfs(root->left);
        dfs(root->right);

        values.pop_back();
    }

    int maxAncestorDiff(TreeNode *diff) {
        values.clear();
        max = INT_MIN;

        dfs(diff);

        return max;
    }
#else
    int dfs(TreeNode *node, int max, int min) {
        if (!node) {
            return max - min;
        }

        max = std::max(max, node->val);
        min = std::min(min, node->val);

        auto left = dfs(node->left, max, min);
        auto right = dfs(node->right, max, min);

        return std::max(left, right);
    }

    int maxAncestorDiff(TreeNode *diff) {
        return dfs(diff, diff->val, diff->val);
    }
#endif
};

TEST_CASE("MaximumDifferenceBetweenNodeAndAncestor", "algorithm") {
    Solution soln;
    Tree testCase0{8, 3, 10, 1, 6, INT_MIN, 14, INT_MIN, INT_MIN, 4, 7, 13};
    Tree testCase1{1, INT_MIN, 2, INT_MIN, 0, 3};

    int actual0 = soln.maxAncestorDiff(testCase0.root);
    int actual1 = soln.maxAncestorDiff(testCase1.root);

    CHECK(actual0 == 7);
    CHECK(actual1 == 3);
}

