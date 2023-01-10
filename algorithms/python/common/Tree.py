from typing import List
from common.TreeNode import TreeNode

class Tree:
    def __init__(self, elements: List[int]):
        self.root = None
        if not elements:
            return

        size = len(elements)
        self.root = TreeNode(elements[0])
        index = 1
        queue: List[TreeNode] = []
        queue.append(self.root)

        while queue:
            node = queue.pop(0)
            if index < size:
                val = elements[index]
                index += 1
                if val != None:
                    node.left = TreeNode(val)
                    queue.append(node.left)
            if index < size:
                val = elements[index]
                index += 1
                if val != None:
                    node.right = TreeNode(val)
                    queue.append(node.right)


