import math
from typing import List

class Problem061:
    def solution(self) -> None:
        target, polygonals = 6, []
        self.__add_triangle(polygonals)
        self.__add_square(polygonals)
        self.__add_pentagonal(polygonals)
        self.__add_hexagonal(polygonals)
        self.__add_heptagonal(polygonals)
        self.__add_octagonal(polygonals)

        length = len(polygonals)
        edges = [[0 for _ in range(length)] for _ in range(length)]
        for i in range(length):
            pivot = polygonals[i]
            for j in range(i + 1, length):
                polygonal = polygonals[j]
                if pivot.step != polygonal.step:
                    if pivot.tail == polygonal.head:
                        edges[i][j] = 1
                    if polygonal.tail == pivot.head:
                        edges[j][i] = 1

        indexes, steps, pivot = [], [False for _ in range(target)], polygonals[0].step
        steps[pivot] = True
        for i in range(length):
            indexes.append(i)
            step = polygonals[i].step
            if step != pivot:
                return
            self.__search(polygonals, edges, i, indexes, steps, target)
            indexes.pop()

    def __add_triangle(self, polygonals: List['__Polygonal']) -> None:
        start, end = math.ceil((math.sqrt(8001) - 1) / 2), math.ceil((math.sqrt(80001) - 1) / 2)
        for i in range(start, end):
            value = i * (i + 1) >> 1
            if value % 100 >= 10:
                polygonals.append(self.__Polygonal(value, 0))

    def __add_square(self, polygonals: List['__Polygonal']) -> None:
        start, end = math.ceil(math.sqrt(1000)), math.ceil(math.sqrt(10000))
        for i in range(start, end):
            value = i * i
            if value % 100 >= 10:
                polygonals.append(self.__Polygonal(value, 1))

    def __add_pentagonal(self, polygonals: List['__Polygonal']) -> None:
        start, end = math.ceil((math.sqrt(24001) + 1) / 6), math.ceil((math.sqrt(240001) + 1) / 6)
        for i in range(start, end):
            value = i * (3 * i - 1) >> 1
            if value % 100 >= 10:
                polygonals.append(self.__Polygonal(value, 2))

    def __add_hexagonal(self, polygonals: List['__Polygonal']) -> None:
        start, end = math.ceil((math.sqrt(8001) + 1) / 4), math.ceil((math.sqrt(80001) + 1) / 4)
        for i in range(start, end):
            value = i * ((i << 1) - 1)
            if value % 100 >= 10:
                polygonals.append(self.__Polygonal(value, 3))

    def __add_heptagonal(self, polygonals: List['__Polygonal']) -> None:
        start, end = math.ceil((math.sqrt(40009) + 3) / 10), math.ceil((math.sqrt(400009) + 3) / 10)
        for i in range(start, end):
            value = i * (5 * i - 3) >> 1
            if value % 100 >= 10:
                polygonals.append(self.__Polygonal(value, 4))

    def __add_octagonal(self, polygonals: List['__Polygonal']) -> None:
        start, end = math.ceil((math.sqrt(12002) + 2) / 6), math.ceil((math.sqrt(120002) + 2) / 6)
        for i in range(start, end):
            value = i * (3 * i - 2)
            if value % 100 >= 10:
                polygonals.append(self.__Polygonal(value, 5))

    def __search(self, polygonals: List['__Polygonal'], edges: List[List[int]], start: int, indexes: List[int], steps: List[bool], target: int) -> None:
        if len(indexes) == target:
            if polygonals[indexes[0]].head == polygonals[indexes[-1]].tail:
                result = 0
                for index in indexes:
                    polygonal = polygonals[index]
                    result += polygonal.head * 100 + polygonal.tail
                print(result)
            return

        for i in range(len(polygonals) - 1, -1, -1):
            if edges[start][i]:
                step = polygonals[i].step
                if not steps[step]:
                    indexes.append(i)
                    steps[step] = True
                    self.__search(polygonals, edges, i, indexes, steps, target)
                    indexes.pop()
                    steps[step] = False

    class __Polygonal:
        def __init__(self, value: int, step: int) -> None:
            self.head, self.tail, self.step, self.next = value // 100, value % 100, step, None
