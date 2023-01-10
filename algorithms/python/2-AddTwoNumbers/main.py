#
# https://leetcode.com/problems/add-two-numbers/
# Medium
# Topics:
#
# The brute force, naive way would be to convert each list to a number, add, then reverse there result.
#
# Time Complexity: O(n), O(3n)
# Space Complexity: O(n)
#
# However, we can be more efficient with things by just iterating once through the lists, tracking the carry
#
# Time Complexity: O(n)
# Space Complexity: O(n)
#

from typing import List
from typing import Optional
from common.ListContainer import ListContainer
from common.ListNode import ListNode

import unittest

class Solution:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        # Trivial rejection
        if not l1:
            return l2
        if not l2:
            return l1

        dummy = ListNode(-1)
        curr = dummy

        carry = 0
        while l1 or l2 or carry:
            l1_val = l1.val if l1 else 0
            l2_val = l2.val if l2 else 0
            sum = l1_val + l2_val + carry
            carry = sum // 10
            node = ListNode(sum % 10)
            curr.next = node
            curr = node
            l1 = l1.next if l1 else None
            l2 = l2.next if l2 else None
        return dummy.next

class TestSolution(unittest.TestCase):
    def setUp(self):
        self.soln = Solution()

    def test_case0(self):
        test_case_a0 = ListContainer([0])
        test_case_b0 = ListContainer([0])
        self.assertCountEqual(self.soln.addTwoNumbers(test_case_a0.head, test_case_b0.head).toVector(), [0])

    def test_case1(self):
        test_case_a1 = ListContainer([0])
        test_case_b1 = ListContainer([1])
        self.assertCountEqual(self.soln.addTwoNumbers(test_case_a1.head, test_case_b1.head).toVector(), [1])

    def test_case2(self):
        test_case_a2 = ListContainer([1])
        test_case_b2 = ListContainer([0])
        self.assertCountEqual(self.soln.addTwoNumbers(test_case_a2.head, test_case_b2.head).toVector(), [1])

    def test_case3(self):
        test_case_a3 = ListContainer([0, 0, 1])
        test_case_b3 = ListContainer([3, 4, 5])
        self.assertCountEqual(self.soln.addTwoNumbers(test_case_a3.head, test_case_b3.head).toVector(), [3, 4, 6])

    def test_case4(self):
        test_case_a4 = ListContainer([2, 4, 3])
        test_case_b4 = ListContainer([5, 6, 4])
        self.assertCountEqual(self.soln.addTwoNumbers(test_case_a4.head, test_case_b4.head).toVector(), [7, 0, 8])

    def test_case5(self):
        test_case_a5 = ListContainer([9, 9, 9, 9, 9, 9, 9])
        test_case_b5 = ListContainer([9, 9, 9, 9])
        self.assertCountEqual(self.soln.addTwoNumbers(test_case_a5.head, test_case_b5.head).toVector(), [8, 9, 9, 9, 0, 0, 0, 1])

    def test_case6(self):
        test_case_a6 = ListContainer([9, 9, 9, 9])
        test_case_b6 = ListContainer([9, 9, 9, 9, 9, 9, 9])
        self.assertCountEqual(self.soln.addTwoNumbers(test_case_a6.head, test_case_b6.head).toVector(), [8, 9, 9, 9, 0, 0, 0, 1])

    def test_case7(self):
        test_case_a7 = ListContainer([9])
        test_case_b7 = ListContainer([1, 9, 9, 9, 9, 9, 9, 9, 9, 9])
        self.assertCountEqual(self.soln.addTwoNumbers(test_case_a7.head, test_case_b7.head).toVector(), [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1])

    def test_case8(self):
        test_case_a8 = ListContainer([1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1])
        test_case_b8 = ListContainer([5, 6, 4])
        self.assertCountEqual(self.soln.addTwoNumbers(test_case_a8.head, test_case_b8.head).toVector(), [6,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1])
