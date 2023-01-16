#
# https:#leetcode.com/problems/moving-average-from-data-stream/
# Easy
# Topics: Array, Design, Queue, Data Stream
#
# One can use a queue to solve this
#
# Time Complexity: O(1)
# Space Complexity: O(n), where n is the size of the moving average
#

from typing import List
from typing import Union
from collections import deque
import unittest

def execute(commands: List[str], args: List[List[int]]) -> List[Union[None, float]]:
    results: List[Union[None, float]] = []
    moving: MovingAverage

    for [i, cmd] in enumerate(commands):
        arg = args[i][0] if len(args[i]) else 0
        if cmd == "MovingAverage":
            moving = MovingAverage(arg)
            results.append(None)
        elif cmd == "next":
            results.append(moving.next(arg))
    return results

class MovingAverage:
    def __init__(self, size: int):
        self.size = size
        self.sum = 0
        self.queue = deque()

    def next(self, val: int) -> float:
        if len(self.queue) == self.size:
            first = self.queue.popleft()
            self.sum -= first
        self.queue.append(val)
        self.sum += val
        return self.sum / len(self.queue)

class TestSolution(unittest.TestCase):
    def setUp(self):
        pass

    def test_case0(self):
        cmds0: List[str] = ["MovingAverage", "next", "next", "next", "next"]
        args0: List[List[int]] = [[3], [1], [10], [3], [5]]
        results0: List[Union[None, float]] = execute(cmds0, args0)
        expected0: List[Union[None, float]] = [None, 1.0, 5.5, 4.66667, 6.0]
        self.assertEqual(len(cmds0), len(results0))
        for i in range(len(results0)):
            self.assertAlmostEqual(expected0[i], results0[i], 5)