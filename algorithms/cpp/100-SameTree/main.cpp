//
// Created by Benjamin Lee on 1/9/23.
// https://leetcode.com/problems/same-tree/
// Easy
// Topics
//

/*
 * We can approach this iteratively or recusively. Recursively is very easy to understand. We do trivial rejection first,
 * and then recursively to the children.
 *
 * Recursive solution will be:
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * Iteratively, this is suited for breadth first search. This uses a queue. We will use two queues, one for p and one
 * for q.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */


#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include "../include/BinarySearchTree.h"
#include <queue>

class Solution {
public:
#ifdef RECURSIVE
    bool isSameTree(TreeNode *p, TreeNode *q) {
        // Trivial checks
        if (!p and !q) return true;
        if (!p or !q) return false;

        if (p->val != q->val) return false;

        return isSameTree(p->left, q->left) and isSameTree(p->right, q->right);
    }
#else
    bool isSameTree(TreeNode *p, TreeNode *q) {
        std::queue<TreeNode *> queue0;
        std::queue<TreeNode *> queue1;

        queue0.push(p);
        queue1.push(q);

        while(queue0.size()) {
            auto node0 = queue0.front();
            auto node1 = queue1.front();

            queue0.pop();
            queue1.pop();

            // Trivial checks
            if (node0 and node1) {
                if (node0->val != node1->val) return false;

                auto left0 = node0->left;
                auto left1 = node1->left;
                if (left0 and left1) {
                    queue0.push(node0->left);
                    queue1.push(node1->left);
                } else if (!(!left0 and !left1)) {
                    return false;
                }

                auto right0 = node0->right;
                auto right1 = node1->right;
                if (right0 and right1) {
                    queue0.push(node0->right);
                    queue1.push(node1->right);
                } else if (!(!right0 and !right1)) {
                    return false;
                }
            } else if (!(!node0 and !node1)) {
                return false;
            }
        }

        return true;
    }
#endif /* RECURSIVE */
};

TEST_CASE("SameTree", "algorithm") {
    Solution soln;
    Tree p0{1, 2, 3};
    Tree q0{1, 2, 3};
    Tree p1{1, 2};
    Tree q1{1, std::numeric_limits<int>::min(), 2};
    Tree p2{1, 2, 1};
    Tree q2{1, 1, 2};

    CHECK(soln.isSameTree(p0.root, q0.root) == true);
    CHECK(soln.isSameTree(p1.root, q1.root) == false);
    CHECK(soln.isSameTree(p2.root, q2.root) == false);
}