//
// Created by Benjamin Lee on 1/8/23.
// https://leetcode.com/problems/binary-tree-preorder-traversal/
// Easy
// Topics:
//

/*
 * This translates to a Depth First Search (DFS).
 *
 * For a refresher, Depth First Search goes down the children. There are 3 types of traversal:
 * Pre-Order: root, left, right
 * In-Order: left, root, right
 * Post-Order: right, root, left
 *
 * We can approach this two ways:
 *
 * Recursion
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * Iterative
 * Iterative approach uses a stack
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
#ifdef RECURSIVE
    void dfs(TreeNode *root, std::vector<int>& results) {
        if (!root) return;

        results.push_back(root->val);

        if (root->left) {
            dfs(root->left, results);
        }

        if (root->right) {
            dfs(root->right, results);
        }
    }

    std::vector<int> preorderTraversal(TreeNode *root) {
        std::vector<int> results;

        dfs(root, results);

        return results;
    }
#else
    std::vector<int> preorderTraversal(TreeNode *root) {
        if (!root) return {};

        std::vector<int> results;
        std::stack<TreeNode *> stack;

        stack.push(root);

        while (stack.size()) {
            auto node = stack.top();
            stack.pop();

            if (node) {
                results.push_back(node->val);
                stack.push(node->right);
                stack.push(node->left);
            }
        }

        return results;
    }
#endif /* RECURSIVE */
};

TEST_CASE("BinaryTreePreorderTraversal", "algorithm") {
    Solution soln;
    Tree testCase0{1, std::numeric_limits<int>::min(), 2, 3};
    Tree testCase1{};
    Tree testCase2{1};
    Tree testCase3{1, 2, 3, 4, 5, 6, 7};

    CHECK(soln.preorderTraversal(testCase0.root) == std::vector<int>{1, 2, 3});
    CHECK(soln.preorderTraversal(testCase1.root) == std::vector<int>{});
    CHECK(soln.preorderTraversal(testCase2.root) == std::vector<int>{1});
    CHECK(soln.preorderTraversal(testCase3.root) == std::vector<int>{1, 2, 4, 5, 3, 6, 7});
}
