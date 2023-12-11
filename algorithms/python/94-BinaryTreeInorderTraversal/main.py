#
# https://leetcode.com/problems/binary-tree-inorder-traversal/
# Easy
# Topics: Array, Tree, Depth First Search, Binary Tree
#
# Inorder traversal is a traversal type used in Depth First Search (DFS). We can do this iteratively or recursively.
# If done iteratively, it is done using a stack

# Time Complexity: O(n)
# Space Complexity: O(n)
#

from typing import List
from typing import Optional
from common.Tree import Tree
from common.TreeNode import TreeNode

import unittest

RECURSIVE = False

if RECURSIVE:
    class Solution:
        def dfs(self, root: Optional[TreeNode], results: List[int]):
            if not root:
                return
            if root.left:
                self.dfs(root.left, results)
            results.append(root.val)
            if root.right:
                self.dfs(root.right, results)

        def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
            results: List[int] = []
            self.dfs(root, results)
            return results
else:
    class Solution:
        def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
            results: List[int] = []
            p: Optional[TreeNode] = root
            stack: List[TreeNode] = []
            while p or stack:
                while p:
                    stack.append(p)
                    p = p.left
                p = stack.pop()
                results.append(p.val)
                p = p.right
            return results

class TestSolution(unittest.TestCase):
    def setUp(self):
        self.soln = Solution()

    def test_case0(self):
        test_case0 = Tree([1, None, 2, 3])
        self.assertCountEqual(self.soln.inorderTraversal(test_case0.root), [1, 3, 2])

    def test_case1(self):
        test_case1 = Tree([])
        self.assertCountEqual(self.soln.inorderTraversal(test_case1.root), [])

    def test_case2(self):
        test_case2 = Tree([1])
        self.assertCountEqual(self.soln.inorderTraversal(test_case2.root), [1])

    def test_case3(self):
        test_case3 = Tree([1, 2, 3, 4, 5, 6, 7])
        self.assertCountEqual(self.soln.inorderTraversal(test_case3.root), [4, 2, 5, 1, 3, 6, 7])
