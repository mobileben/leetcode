#
# https://leetcode.com/problems/same-tree/
# Easy
# Topics: Tree, Depth First Search, Breadth First Search, Binary Tree
#
# This can be solved recursively or iteratively.
#
# The recursive approach is the most intuitive. Trivial checks up front followed by recursive calls for the children
#
# Time Complexity: O(n)
# Space Complexity: O(n)
#
# For the iterative approach, we can use Breadth First Search. In this case we can use a queue. We will use two queues
#
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
        def isSameTree(self, p: Optional[TreeNode], q: Optional[TreeNode]) -> bool:
            # Trivial Checks
            if p is None and q is None:
                return True
            if p is None or q is None:
                return False

            if p.val != q.val:
                return False

            return self.isSameTree(p.left, q.left) and self.isSameTree(p.right, q.right)

else:
    class Solution:
        def isSameTree(self, p: Optional[TreeNode], q: Optional[TreeNode]) -> bool:
            queue0: List[TreeNode] = []
            queue1: List[TreeNode] = []

            if p is None and q is None:
                return True
            if p is None or q is None:
                return False

            queue0.append(p)
            queue1.append(q)

            while len(queue0):
                node0 = queue0.pop(0)
                node1 = queue1.pop(0)

                if node0 and node1:
                    if node0.val != node1.val:
                        return False
                    left0 = node0.left
                    left1 = node1.left
                    if left0 and left1:
                        queue0.append(left0)
                        queue1.append(left1)
                    elif not (not left0 and not left1):
                        return False
                    right0 = node0.right
                    right1 = node1.right
                    if right0 and right1:
                        queue0.append(right0)
                        queue1.append(right1)
                    elif not (not right0 and not right1):
                        return False
                elif not (not node0 and not node1):
                    return False
            return True

class TestSolution(unittest.TestCase):
    def setUp(self):
        self.soln = Solution()

    def test_case0(self):
        p0 = Tree([1, 2, 3])
        q0 = Tree([1, 2, 3])
        self.assertTrue(self.soln.isSameTree(p0.root, q0.root))

    def test_case1(self):
        p1 = Tree([1, 2])
        q1 = Tree([1, None, 2])
        self.assertFalse(self.soln.isSameTree(p1.root, q1.root))

    def test_case2(self):
        p2 = Tree([1, 2, 1])
        q2 = Tree([1, 1, 2])
        self.assertFalse(self.soln.isSameTree(p2.root, q2.root))