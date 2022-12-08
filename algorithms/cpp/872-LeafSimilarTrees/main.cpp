//
// Created by Benjamin Lee on 12/8/22.
// https://leetcode.com/problems/leaf-similar-trees/
//

/*
 *  This is a depth first search (DFS) algorithm.
 *
 *  This can be solved iteratively or recursively
 *
 *  Time Complexity: O(T1 + T2)
 *  Space Complexity: O(T1 + T2)
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <stack>

#include "../include/BinarySearchTree.h"

#define RECURSIVE

class Solution {
public:
#ifdef RECURSIVE
    void dfs(TreeNode *root, std::vector<int>& leafs) {
        if (!root) return;

        if (!root->left && !root->right) {
            leafs.push_back(root->val);
        }
        if (root->left) dfs(root->left, leafs);
        if (root->right) dfs(root->right, leafs);
    }

    bool leafSimilar(TreeNode *root1, TreeNode *root2) {
        std::vector<int> leafs1;
        std::vector<int> leafs2;

        dfs(root1, leafs1);
        dfs(root2, leafs2);

        return leafs1 == leafs2;
    }
#else
    std::vector<int> getLeafs(TreeNode *root) {
        std::vector<int> leafs;
        std::stack<TreeNode *> stack;
        stack.push(root);

        while (!stack.empty()) {
            auto node = stack.top();
            stack.pop();

            if(!node->left && !node->right) {
                leafs.push_back(node->val);
            } else {
                if (node->left) {
                    stack.push(node->left);
                } else {

                }
                if (node->right) {
                    stack.push(node->right);
                }
            }
        }
        return leafs;
    }

    bool leafSimilar(TreeNode *root1, TreeNode *root2) {
        auto leafs1 = getLeafs(root1);
        auto leafs2 = getLeafs(root2);

        return leafs1 == leafs2;
    }
#endif /* RECURSIVE */
};

TEST_CASE("LeafSimilarTrees", "algorithm") {
    Solution soln;
    Tree testCaseA_0{10};
    Tree testCaseB_0{20};
    Tree testCaseA_1{10};
    Tree testCaseB_1{20, 2};
    Tree testCaseA_2{10};
    Tree testCaseB_2{20, INT_MIN, 21};
    Tree testCaseA_3{3, 5, 1, 6, 2, 9, 8, INT_MIN, INT_MIN, 7, 4};
    Tree testCaseB_3{3, 5, 1, 6, 7, 4, 2, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, 9, 8};
    Tree testCaseA_4{1, 2, 3};
    Tree testCaseB_4{1, 3, 2};

    auto actual0 = soln.leafSimilar(testCaseA_0.root, testCaseB_0.root);
    auto actual1 = soln.leafSimilar(testCaseA_1.root, testCaseB_1.root);
    auto actual2 = soln.leafSimilar(testCaseA_2.root, testCaseB_2.root);
    auto actual3 = soln.leafSimilar(testCaseA_3.root, testCaseB_3.root);
    auto actual4 = soln.leafSimilar(testCaseA_4.root, testCaseB_4.root);

    CHECK(actual0 == false);
    CHECK(actual1 == false);
    CHECK(actual2 == false);
    CHECK(actual3 == true);
    CHECK(actual4 == false);
}


