#
# https://leetcode.com/problems/design-circular-queue/
# Medium
# Topics: Array, Linked List, Design, Queue
#
# The brute force way is to have a head and tail pointer referencing the index into a std::vector.
#
# We can clean this up by tracking only count and capacity, and using modulus to reference the right index.
#
# Lastly, we could also use a singly linked list to implement the queue. If one opts for supporting singly linked lists
# one will have to contend with memory management, which includes the costs of the allocation and deallocation. One
# way around this is to have a static pool of list elements to draw from.
#
# Time Complexity: O(1)
# Space Complexity: O(n)
#

from typing import List
from typing import Union
import unittest

def execute(commands: List[str], args: List[List[int]]):
    results: List[Union[None, bool, int]] = []
    queue: MyCircularQueue

    for [i, cmd] in enumerate(commands):
        arg = args[i][0] if len(args[i]) else 0

        if cmd == "MyCircularQueue":
            queue = MyCircularQueue(arg)
            results.append(None)
        elif cmd == "enQueue":
            results.append(queue.enQueue(arg))
        elif cmd == "deQueue":
            results.append(queue.deQueue())
        elif cmd == "Front":
            results.append(queue.Front())
        elif cmd == "Rear":
            results.append(queue.Rear())
        elif cmd == "isEmpty":
            results.append(queue.isEmpty())
        elif cmd == "isFull":
            results.append(queue.isFull())
    return results

class MyCircularQueue:
    def __init__(self, k: int):
        self.v = [0] * k
        self.head = 0
        self.count = 0
        self.capacity = k

    def enQueue(self, value: int) -> bool:
        if self.count == self.capacity:
            return False
        self.v[(self.head + self.count) % self.capacity] = value
        self.count += 1
        return True

    def deQueue(self) -> bool:
        if self.count == 0:
            return False
        self.head = (self.head + 1) % self.capacity
        self.count -= 1
        return True

    def Front(self) -> int:
        return self.v[self.head] if self.count > 0 else -1

    def Rear(self) -> int:
        return self.v[(self.head + self.count - 1) % self.capacity] if self.count > 0 else -1

    def isEmpty(self) -> bool:
        return self.count == 0

    def isFull(self) -> bool:
        return self.count == self.capacity

class TestSolution(unittest.TestCase):
    def setUp(self):
        pass

    def test_case0(self):
        commands0 = ["MyCircularQueue", "enQueue", "enQueue", "enQueue", "enQueue", "Rear", "isFull", "deQueue", "enQueue", "Rear"]
        args0 = [[3], [1], [2], [3], [4], [], [], [], [4], []]
        self.assertEqual(execute(commands0, args0), [None, True, True, True, False, 3, True, True, True, 4])

    def test_case1(self):
        commands1 = ["MyCircularQueue", "enQueue", "Rear", "Rear", "deQueue", "enQueue", "Rear", "deQueue", "Front", "deQueue",
                     "deQueue", "deQueue"]
        args1 = [[6], [6], [], [], [], [5], [], [], [], [], [], []]
        self.assertEqual(execute(commands1, args1), [None, True, 6, 6, True, True, 5, True, -1, False, False, False])

    def test_case2(self):
        commands2 = ["MyCircularQueue", "enQueue", "enQueue", "deQueue", "enQueue", "deQueue", "enQueue", "deQueue", "enQueue",
         "deQueue", "Front"]
        args2 = [[2], [1], [2], [], [3], [], [3], [], [3], [], []]
        self.assertEqual(execute(commands2, args2), [None, True, True, True, True, True, True, True, True, True, 3])