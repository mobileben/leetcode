#
# https://leetcode.com/problems/minimum-time-to-collect-all-apples-in-a-tree/
# Medium
# Topics: Hash Table, Tree, Depth-First Search, Breadth-First Search
#
# Time Complexity: O(n)
# Space Complexity: O(n)
#

from typing import List
from typing import Dict

import unittest

class Solution:
    def dfs(self, node: int, parent: int, adjacency: Dict[int, List[int]], hasApples: List[bool]) -> int:
        total: int = 0
        for child in adjacency[node]:
            if child == parent:
                continue
            time = self.dfs(child, node, adjacency, hasApples)
            # time > 0 when our child has an apple OR if a sub-child has an apple, we need to add 2 for the back and
            # forth
            if time or hasApples[child]:
                total += time + 2
        return total

    def minTime(self, n: int, edges: List[List[int]], hasApples: List[bool]) -> int:
        adjacency: Dict[int, List[int]] = {}
        for e in edges:
            if not adjacency.get(e[0]):
                adjacency[e[0]] = []
            adjacency[e[0]].append(e[1])
            if not adjacency.get(e[1]):
                adjacency[e[1]] = []
            adjacency[e[1]].append(e[0])
        return self.dfs(0, -1, adjacency, hasApples)

class TestSolution(unittest.TestCase):
    def setUp(self):
        self.soln = Solution()

    def test_case0(self):
        edges0 = [[0, 1], [0, 2], [1, 4], [1, 5], [2, 3], [2, 6]]
        hasApples0 = [False, False, True, False, True, True, False]
        self.assertEqual(self.soln.minTime(7, edges0, hasApples0), 8)

    def test_case1(self):
        edges1 = [[0, 1], [0, 2], [1, 4], [1, 5], [2, 3], [2, 6]]
        hasApples1 = [False, False, True, False, False, True, False];
        self.assertEqual(self.soln.minTime(7, edges1, hasApples1), 6)

    def test_case2(self):
        edges2 = [[0, 1], [0, 2], [1, 4], [1, 5], [2, 3], [2, 6]]
        hasApples2 = [False, False, False, False, False, False, False];
        self.assertEqual(self.soln.minTime(7, edges2, hasApples2), 0)
