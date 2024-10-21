import sys
from heapq import heappush, heappop, heapify


def dijkstra(graph, source, destination):
    inf = sys.maxsize
    node_data = {
        'A': {'cost': inf, 'pred': []},
        'B': {'cost': inf, 'pred': []},
        'C': {'cost': inf, 'pred': []},
        'D': {'cost': inf, 'pred': []},
        'E': {'cost': inf, 'pred': []},
        'F': {'cost': inf, 'pred': []},
    }

    node_data[source]['cost'] = 0
    visited = []
    temp = source

    while temp != destination:
        if temp not in visited:
            visited.append(temp)

            for neighbor, cost in graph[temp].items():
                if neighbor not in visited:
                    cost = node_data[temp]['cost'] + cost
                    if cost < node_data[neighbor]['cost']:
                        node_data[neighbor]['cost'] = cost
                        node_data[neighbor]['pred'].append(temp)

            



graph = {
    'A': {'B': 2, 'C': 4},
    'B': {'A': 2, 'C': 3, 'D': 8},
    'C': {'A': 4, 'B': 3, 'D': 2, 'E': 5},
    'D': {'B': 8, 'C': 2, 'E': 11, 'F': 22},
    'E': {'C': 5, 'D': 11, 'F': 1},
    'F': {'D': 22, 'E': 1}
}

if __name__ == "__main__":
    dijkstra(graph, 'A', 'F')