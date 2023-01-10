from __future__ import annotations
from typing import List
from typing import Optional

class ListNode:
    def __init__(self, val: int = 0, next: Optional[ListNode] = None):
        self.val = val
        self.next = next

    def __eq__(self, other):
        return self.val == other.val

    def __str__(self):
        return f'{self.val}'

    def toVector(self):
        out: List[int] = []
        node = self
        while node:
            out.append(node.val)
            node = node.next
        return out
