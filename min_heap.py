from collections import deque

class Node:
    def __init__(self, data: int, parent = None, leftChild = None, rightChild = None):
        self.data = data
        self.left = leftChild
        self.right = rightChild
        self.parent = parent

class Heap:
    def __init__(self, values: list):
        self.root = Node(values[0])
        self.values = values

    def insert(self, node: Node, current_node: Node):
        if current_node.data >= node.data:
            if current_node.left is None:
                current_node.left = node
                node.parent = current_node
            else:
                self.insert(node, current_node.left)

        elif current_node.data < node.data:
            if current_node.right is None:
                current_node.right = node
                node.parent = current_node
            else:
                self.insert(node, current_node.right)

    def tree_construct(self):
        for i in self.values[1:]:
            self.insert(Node(i), self.root)

        self.print_tree()

    def print_tree(self):
        if not self.root:
            return
        
        queue = deque([self.root])
        nodes = []

        while queue:
            node = queue.popleft()
            nodes.append(node.data)

            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)

        print(nodes)
    
    def min_heep_tree_construction(self):
        pass



if __name__ == "__main__":
    values = [10, 30, 24, 59, 64, 11, 80, 5, 50, 29]

    tree = Heap(values)
    tree.tree_construct()

    


    
        