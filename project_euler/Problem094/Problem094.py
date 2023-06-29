import math
from typing import List

class Problem094:
    def solution(self) -> None:
        target, index, result = 1000000000, [2, 1], 0
        while True:
            index[0], index[1] = (index[0] << 1) + index[1] * 3, index[0] + (index[1] << 1)
            value = self.__get_triangle(index, -1, target)
            if -1 == value:
                break
            result += value

            value = self.__get_triangle(index, 1, target)
            if -1 == value:
                break
            result += value
        print(result)

    def __get_triangle(self, index: List[int], offset: int, target: int) -> int:
        perimeter = (index[0] + offset) << 1
        if perimeter >= target:
            return -1

        length = ((index[0] << 1) + offset) / 3
        if abs(math.floor(length + 0.5) - length) > 0.00000001:
            return 0
        area = (length + offset) * index[1] / 2
        if abs(math.floor(area + 0.5) - area) > 0.00000001:
            return 0
        return perimeter
