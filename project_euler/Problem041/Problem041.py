import math
from typing import List

class Problem041:
    def solution(self) -> None:
        elements = [7, 6, 5, 4, 3, 2, 1]
        result = self.__permutation(elements, 0, len(elements), 0)
        print(result)

    def __permutation(self, elements: List[int], index: int, length: int, pivot: int) -> int:
        if index == length:
            result = 0
            for element in elements:
                result = result * 10 + element
            if self.__is_prime(result):
                return max(result, pivot)
            return pivot

        result = self.__permutation(elements, index + 1, length, pivot)
        for i in range(index + 1, length):
            elements[index], elements[i] = elements[i], elements[index]
            result = self.__permutation(elements, index + 1, length, result)
            elements[index], elements[i] = elements[i], elements[index]
        return result

    def __is_prime(self, value: int) -> bool:
        if 1 != value % 6 and 5 != value % 6:
            return 2 == value or 3 == value

        border = int(math.sqrt(value))
        for i in range(5, border + 1, 6):
            if not value % i or not value % (i + 2):
                return False
        return 1 != value
