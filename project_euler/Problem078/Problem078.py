import math
from typing import List

class Problem078:
    def solution(self) -> None:
        target, ways = 1000000, [1, 1]
        result = 2
        while True:
            way = self.__get_ways(result, ways)
            if not way % target:
                print(result)
                return
            result += 1

    def __get_ways(self, target: int, ways: List[int]) -> int:
        delta = int(math.sqrt(target * 24 + 1))
        borders = [(delta + 1) // 6 + 1, (delta - 1) // 6 + 1]
        result, factor = 0, 1
        for i in range(1, borders[1]):
            result += factor * ways[target - (i * (i * 3 - 1) >> 1)] + factor * ways[target - (i * (i * 3 + 1) >> 1)]
            factor *= -1
        if borders[0] != borders[1]:
            result += factor * ways[target - (borders[1] * (borders[1] * 3 - 1) >> 1)]
        ways.append(result)
        return result
