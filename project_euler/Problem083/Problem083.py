import heapq
from typing import List

class Problem083:
    def solution(self) -> None:
        file_name, border = 'matrix.txt', 80
        target = [[0 for _ in range(border)] for _ in range(border)]
        with open(file_name, 'r') as handle:
            index = 0
            for line in handle:
                elements = line.strip().split(' ')
                for i, element in enumerate(elements):
                    target[index][i] = int(element)
                index += 1

        length = border * border
        edges = [[0 for _ in range(length)] for _ in range(length)]
        for i in range(border):
            for j in range(border):
                if i > 0:
                    edges[i * border + j][(i - 1) * border + j] = target[i - 1][j]
                if j > 0:
                    edges[i * border + j][i * border + j - 1] = target[i][j - 1]
                if i < border - 1:
                    edges[i * border + j][(i + 1) * border + j] = target[i + 1][j]
                if j < border - 1:
                    edges[i * border + j][i * border + j + 1] = target[i][j + 1]

        ways = [0 for _ in range(length)]
        self.__search(edges, length, ways)
        print(ways[-1] + target[0][0])

    def __search(self, edges: List[List[int]], length: int, ways: List[int]) -> None:
        visited, queue = [False for _ in range(length)], [self.__Heap(0, 0)]
        while queue:
            node = heapq.heappop(queue)
            index, weight = node.index, node.weight
            if visited[index]:
                continue

            ways[index], visited[index] = weight, True
            for i in range(length):
                if edges[index][i] and not visited[i]:
                    heapq.heappush(queue, self.__Heap(i, weight + edges[index][i]))

    class __Heap:
        def __init__(self, index: int, weight: int) -> None:
            self.index, self.weight = index, weight

        def __lt__(self, other: '__Heap') -> None:
            return self.weight < other.weight
