#
# https://leetcode.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/
# Medium
# Topics: Hash Table, Tree, Depth-First Search, Breadth-First Search, Counting
#
# This is a graph traversal problem. We'll choose Depth-First Search as the search to use. A key detail to note
# is that these are undirected graphs. This becomes important because a graph with edges defined as follows:
#
# {{0, 2}, {0, 3}, {1, 2}}
#
# if one was ignoring the unidirection, would look like
#
# 1   0
#  \ / \
#   2   3
#
# which is wrong, it actually looks like this
#
#     0
#    / \
#   2   3
#  /
# 1
#
# As we build our adjacency list, we need to add both edges to the adjacency list.
#
# Time Complexity: O(n), O(26n) -> O(n)
# Space Complexity: O(n), O(26n) -> O(n)
#
# Breadth-First Search may also be employed here. When used, we will be moving bottom up, as opposed to top to bottom, as we traditionally do.
# This way, as we move upwards, we can populate the results. To do this, we need to isolate all leafs. As we work upwards, we will be pruning our
# leafs, which in turn will create more leafs that we will need to process.
#
# Time Complexity: O(n), O(26n) -> O(n)
# Space Complexity: O(n), O(26n) -> O(n)
#

from collections import Counter
from collections import defaultdict
from typing import Dict
from typing import List

import unittest

BRUTE = False

if BRUTE:
    class Solution:
        def dfs(self, node: int, parent: int, adj: Dict[int, List[int]], labels: str, results: List[int]):
            counts: List[int] = [0] * 26
            counts[ord(labels[node]) - ord('a')] = 1
            for child in adj[node]:
                if child == parent:
                    continue
                totals = self.dfs(child, node, adj, labels, results)
                for i in range(26):
                    counts[i] += totals[i]
            results[node] = counts[ord(labels[node]) - ord('a')]
            return counts

        def countSubTrees(self, n: int, edges: List[List[int]], labels: str):
            adj: Dict[int, List[int]] = defaultdict(list)
            for e in edges:
                adj[e[0]].append(e[1])
                adj[e[1]].append(e[0])

            results = [0] * n
            self.dfs(0, -1, adj, labels, results)
            return results
else:
    class Solution:
        def dfs(self, node: int, parent: int, adj: Dict[int, List[int]], labels: str, results: List[int]):
            counts = Counter()
            for child in adj[node]:
                if child == parent:
                    continue
                counts += self.dfs(child, node, adj, labels, results)
            counts[labels[node]] += 1
            results[node] = counts[labels[node]]
            return counts

        def countSubTrees(self, n: int, edges: List[List[int]], labels: str):
            adj: Dict[int, List[int]] = defaultdict(list)
            for e in edges:
                adj[e[0]].append(e[1])
                adj[e[1]].append(e[0])

            results = [0] * n
            self.dfs(0, -1, adj, labels, results)
            return results

class TestSolution(unittest.TestCase):
    def setUp(self):
        self.soln = Solution()

    def test_case0(self):
        edges0: List[List[int]] = [[0, 1], [0, 2], [1, 4], [1, 5], [2, 3], [2, 6]]
        labels0 = "abaedcd"
        self.assertEqual(self.soln.countSubTrees(7, edges0, labels0), [2, 1, 1, 1, 1, 1, 1])

    def test_case1(self):
        edges1: List[List[int]] = [[0, 1], [1, 2], [0, 3]]
        labels1 = "bbbb"
        self.assertEqual(self.soln.countSubTrees(4, edges1, labels1), [4, 2, 1, 1])

    def test_case2(self):
        edges2: List[List[int]] = [[0, 2], [0, 3], [1, 2]]
        labels2 = "aeed"
        self.assertEqual(self.soln.countSubTrees(4, edges2, labels2), [1, 1, 2, 1])
