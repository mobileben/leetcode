from typing import List
from typing import Optional
from common.ListNode import ListNode

class ListContainer:
    def __init__(self, elements: List[int]):
        self.head = None
        curr: Optional[ListNode] = None
        for elem in elements:
            node = ListNode(elem)
            if not curr:
                self.head = node
            else:
                curr.next = node
            curr = node

    def __eq__(self, other):
        if self.size != other.size():
            return False
        l_node = self.node
        r_node = other.node
        while l_node and r_node:
            if l_node.val != r_node.val:
                return False
            l_node = l_node.next
            r_node = r_node.next
        return True

    def __str__(self):
        node = self.head
        out = ""
        while node:
            out += f'{self.val} '
            node = node.next
        return out

    def size(self) -> int:
        count = 0
        node = self.head
        while node:
            count += 1
            node = node.next
        return count

    def add(self, x: int):
        if not self.head:
            self.head = ListNode(x)
        else:
            node = self.head
            while node:
                if not node.next:
                    node.next = ListNode(x)
                    break
                node = node.next

    def toVector(self) -> List[int]:
        out: List[int] = []
        node = self.head
        while node:
            out.append(node.val)
            node = node.next
        return out
