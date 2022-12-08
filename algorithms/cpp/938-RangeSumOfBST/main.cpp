//
// Created by Benjamin Lee on 12/6/22.
// https://leetcode.com/problems/range-sum-of-bst/
//

/*
 *
 * The brute force method would be to traverse every node regardless.
 *
 * The best approach here is to use a Depth First Search. This can be approached iteratively or recursively.
 * When using depth sort, we also can be smarter about which nodes we look at.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <stack>
#include "../include/BinarySearchTree.h"

class Solution {
public:
#ifdef BRUTE
    int rangeSumBST(TreeNode *root, int low, int high) {
        if (!root) {
            return 0;
        }

        int sum = 0;

        if (root->val >= low && root->val <= high) {
            sum += root->val;
        }
        if (root->left) {
            sum += rangeSumBST(root->left, low, high);
        }
        if (root->right) {
            sum += rangeSumBST(root->right, low, high);
        }

        return sum;
    }
#elif defined(RECURSIVE)
    int rangeSumBST(TreeNode *root, int low, int high) {
        if (!root) return 0;
        int sum = 0;
        if (root->val >= low && root->val <= high) {
            sum += root->val;
        }
        if (low < root->val) {
            sum += rangeSumBST(root->left, low, high);
        }
        if (root->val < high) {
            sum += rangeSumBST(root->right, low, high);
        }
        return sum;
    }
#else
    int rangeSumBST(TreeNode *root, int low, int high) {
        if (!root) return 0;

        int sum = 0;
        std::stack<TreeNode *> stack;
        stack.push(root);

        while (!stack.empty()) {
            auto node = stack.top();
            stack.pop();

            if (node->val >= low && node->val <= high) {
                sum += node->val;
            }
            if (node->left) {
                stack.push(node->left);
            }
            if (node->right) {
                stack.push(node->right);
            }
        }
        return sum;
    }
#endif /* BRUTE */
};

TEST_CASE("RangeSumOfBST", "algorithm") {
    Solution soln;
    Tree testCase0{10, 5, 15, 3, 7, INT_MIN, 18};
    Tree testCase1{10, 5, 15, 3, 7, 13, 18, 1, INT_MIN, 6};

    auto actual0 = soln.rangeSumBST(testCase0.root, 7, 15);
    auto actual1 = soln.rangeSumBST(testCase1.root, 6, 10);

    CHECK(actual0 == 32);
    CHECK(actual1 == 23);
}

