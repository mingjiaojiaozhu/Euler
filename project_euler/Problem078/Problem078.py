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
        result, factor = 0, 1
        for i in range(1, target + 1):
            index = target - (i * (i * 3 - 1) >> 1)
            if index < 0:
                break
            result += factor * ways[index]
            index = target - (i * (i * 3 + 1) >> 1)
            if index < 0:
                break
            result += factor * ways[index]
            factor *= -1
        ways.append(result)
        return result
