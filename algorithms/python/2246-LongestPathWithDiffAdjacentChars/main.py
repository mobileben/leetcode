#
# https://leetcode.com/problems/longest-path-with-different-adjacent-characters/
# Hard
# Topics: Array, String, Tree, Depth-First Search, Graph, Topological Sort
#
# Depth-First Search is a good approach to solve this. When approaching this problem we can look at a few cases
#
# {-1}
# "a"
# This will result in 1: 0
# 0-a
#
#
# {-1, 0}
# "aa"
# This will result in 1: 0 or 1
#
#  0-a
#  /
# 1-a
#
# {-1, 0}
# "ab"
# This will result in 2: 1 - 0
#  0-a
#  /
# 1-b
#
# {-1, 0, 0}
# "aab"
# This will result in 2: 2-0
#
#  0-a
#  /  \
# 1-a 2-b
#
# {-1, 0, 0}
# "abb"
# This will result in 3: 1 - 0 - 2
#
#  0-a
#  /  \
# 1-a 2-b
#
# {-1, 0, 0, 1}
# "abbc"
# This will result in 4: 3 - 1 - 0 - 2
#    0-a
#    / \
#  1-b 2-b
#  /
# 3-c
#
# {-1, 0, 0, 1, 3, 3}
# "aaebcd"
# This will result in 5: 4 - 3 - 1 - 0 - 2
#      0-a
#      / \
#    1-d 2-e
#    /
#  3-b
#  /  \
# 4-e 5-d
#
# What we can see is that the longest path is actually dependent on the 2 longest legs/paths/chains. This means to
# solve, we want to determine the top 2 legs (if applicable)
#
#
# Time Complexity: O(n)
# Space Complexity: O(n)
#

from typing import Dict
from typing import List
from collections import defaultdict

import unittest

class Solution:
    def __init__(self):
        self.max = 0

    def dfs(self, node: int, adj: Dict[int, List[int]], s: str) -> int:
        max1: int = 0 # Max leg
        max2: int = 0 # Second to max leg

        for child in adj[node]:
            leg: int = self.dfs(child, adj, s)
            if s[child] == s[node]:
                continue
            if leg > max1:
                max2 = max1
                max1 = leg
            elif leg > max2:
                max2 = leg

        total: int = max1 + max2 + 1
        if total > self.max:
            self.max = total

        return max1 + 1


    def longestPath(self, parent: List[int], s: str) -> int:
        self.max = 0
        adj: Dict[int, List[int]] = defaultdict(list)
        for i in range(1, len(parent)):
            adj[parent[i]].append(i)

        self.dfs(0, adj, s)

        return self.max


class TestSolution(unittest.TestCase):
    def setUp(self):
        self.soln = Solution()

    def test_case0(self):
        parent0: List[int] = [-1]
        s0: str = "a"
        self.assertEqual(self.soln.longestPath(parent0, s0), 1)

    def test_case1(self):
        parent1: List[int] = [-1, 0]
        s1: str = "aa"
        self.assertEqual(self.soln.longestPath(parent1, s1), 1)

    def test_case2(self):
        parent2: List[int] = [-1, 0]
        s1: str = "ab"
        self.assertEqual(self.soln.longestPath(parent2, s2), 2)

    def test_case3(self):
        parent0: List[int] = [-1, 0, 1]
        s0: str = "aab"
        self.assertEqual(self.soln.longestPath(parent3, s3), 2)

    def test_case4(self):
        parent4: List[int] = [-1, 0, 0, 0]
        s4: str = "aabc"
        self.assertEqual(self.soln.longestPath(parent4, s4), 2)

    def test_case5(self):
        parent5: List[int] = [-1, 0, 0, 1, 1, 2]
        s5: str = "abacbe"
        self.assertEqual(self.soln.longestPath(parent5, s5), 3)

    def test_case6(self):
        parent6: List[int] = [-1, 0, 0, 1, 3, 3]
        s6: str = "aaebcd"
        self.assertEqual(self.soln.longestPath(parent6, s6), 3)

    def test_case7(self):
        parent7: List[int] = [-1, 0, 0, 1, 3, 3, 4, 5]
        s7: str = "aaebcdfg"
        self.assertEqual(self.soln.longestPath(parent7, s7), 5)
