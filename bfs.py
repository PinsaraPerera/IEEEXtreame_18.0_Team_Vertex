from random import randint
import collections as cl

class Node:
    def __init__(self, left_child, right_child, parent, value = 0):
        self.left = left_child
        self.right = right_child
        self.parent = parent
        self.value = value

class Graph:
    def graph_traverse(graph, root):

        visited = []
        queue = cl.deque([root])

        while queue:
            vertex = queue.popleft()

            if vertex not in visited:
                visited.append(vertex)

            for i in graph[vertex]:
                if i not in visited:
                    queue.append(i)

        print(visited)

                
graph = {
    "1" : ["2", "3"],
    "2" : ["1", "4", "5"],
    "3" : ["1", "6", "7"],
    "4" : ["2"],
    "5" : ["2"],
    "6" : ["3"],
    "7" : ["3"]
}

Graph.graph_traverse(graph, "1")







