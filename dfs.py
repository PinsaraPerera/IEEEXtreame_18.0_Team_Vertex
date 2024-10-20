
class Stack:
    def __init__(self):
        self.items = []

    def push(self, item):
        self.items.append(item)

    def pop(self):
        if not self.is_empty():
            return self.items.pop()
        
    def peek(self):
        if not self.is_empty():
            return self.items[-1]
        
    def is_empty(self):
        return len(self.items) == 0
    
    def __contains__(self, item):
        return item in self.items

    

class Graph:
    @staticmethod
    def traverse(graph, root):
        stack = Stack()
        stack.push(root)

        visited = []

        while not stack.is_empty():
            vertex = stack.pop()
            
            if vertex not in visited:
                visited.append(vertex)

            for neighbor in graph[vertex]:
                if neighbor not in visited and neighbor not in stack:
                    stack.push(neighbor)

        print(visited)



graph = {
    'A':['B', 'C', 'D'],
    'B':['A', 'E'],
    'C':['A', 'D', 'E'],
    'D':['A', 'C'],
    'E':['B', 'C']
}

Graph.traverse(graph, 'B')