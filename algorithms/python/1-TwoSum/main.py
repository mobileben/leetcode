#
# https://leetcode.com/problems/two-sum/
# Easy
# Topics: Array, Hash Table
#
# We can do a one pass loop of our list. As we traverse the list, we check to see if the addend we need is in the dict.
# If it is, we have our answer. If it is not, we simply add our current element. Eventually, if the other addend exists
# we will encounter it.
#
# Time Complexity: O(n)
# Space Complexity: O(n)
#

from typing import List
from typing import Dict

import unittest

class Solution:
    def __init__(self):
        pass

    def twoSum(self, nums: List[int], target: int) -> List[int]:
        map: Dict[int, int] = dict()

        for idx, x in enumerate(nums):
            diff = target - x
            if diff in map:
                return [map[diff], idx]
            map[x] = idx
        return list()

class TestSolution(unittest.TestCase):
    def setUp(self):
        self.soln = Solution()

    def test_case0(self):
        test_case0 = [2, 7, 11, 15]
        self.assertCountEqual(self.soln.twoSum(test_case0, 9), [0, 1])

    def test_case1(self):
        test_case1 = [3, 2, 4]
        self.assertCountEqual(self.soln.twoSum(test_case1, 6), [1, 2])
