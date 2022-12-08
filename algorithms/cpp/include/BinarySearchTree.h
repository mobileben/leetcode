//
// Created by Benjamin Lee on 12/8/22.
//

#ifndef LEETCODE_BINARYSEARCHTREE_H
#define LEETCODE_BINARYSEARCHTREE_H

#include <queue>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct Tree {
    TreeNode *root;
    Tree() : root(nullptr) {}
    Tree(std::initializer_list<int> elements) : root(nullptr) {
        if (!elements.size()) return;

        std::vector<int> v(elements);

        int index = 0;
        int len = elements.size();
        std::queue<TreeNode *> queue;

        TreeNode *node;
        root = new TreeNode(v[index++]);
        queue.push(root);

        while (!queue.empty()) {
            node = queue.front();
            queue.pop();

            auto next = index + 1;
            if (index < len) {
                auto val = v[index++];
                if (val != std::numeric_limits<int>::min()) {
                    auto child = new TreeNode(val);
                    node->left = child;
                    queue.push(child);
                }
            }
            if (index < len) {
                auto val = v[index++];
                if (val != std::numeric_limits<int>::min()) {
                    auto child = new TreeNode(val);
                    node->right = child;
                    queue.push(child);
                }
            }
        }
    }
};

#endif //LEETCODE_BINARYSEARCHTREE_H
