//
// Created by Benjamin Lee on 12/9/23.
// https://leetcode.com/problems/binary-tree-inorder-traversal/
// Easy
// Topics: Stack, Tree, Depth-First Search, Binary Tree
//

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <stack>
#include "../include/BinarySearchTree.h"

class Solution {
public:
#ifdef RECURSIVE
    void dfs(TreeNode *root, std::vector<int>& results) {
        if (!root) return;

        if (root->left) dfs(root->left, results);

        results.push_back(root->val);

        if (root->right) dfs(root->right, results);
    }

    std::vector<int> inorderTraversal(TreeNode *root) {
        std::vector<int> results;
        dfs(root, results);
        return results;
    }
#else
    std::vector<int> inorderTraversal(TreeNode *root) {
        std::vector<int> results;
        std::stack<TreeNode *> stack;
        auto p = root;

        while (p or not stack.empty()) {
            while(p) {
                stack.push(p);
                p = p->left;
            }
            p = stack.top();
            stack.pop();
            results.push_back(p->val);
            p = p->right;
        }
        return results;
    }
#endif /* RECURSIVE */
};

TEST_CASE("BinaryTreeInorderTraversal", "algorithm") {
    Solution soln;
    Tree testCase0{1, std::numeric_limits<int>::min(), 2, 3};
    Tree testCase1{};
    Tree testCase2{1};
    Tree testCase3{1, 2, 3, 4, 5, 6, 7};

    CHECK(soln.inorderTraversal(testCase0.root) == std::vector<int>{1, 3, 2});
    CHECK(soln.inorderTraversal(testCase1.root) == std::vector<int>{});
    CHECK(soln.inorderTraversal(testCase2.root) == std::vector<int>{1});
    CHECK(soln.inorderTraversal(testCase3.root) == std::vector<int>{4, 2, 5, 1, 6, 3, 7});
}