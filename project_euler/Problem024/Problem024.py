from typing import List

class Problem024:
    def solution(self) -> None:
        target, elements = 1000000, [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
        self.__permutation(target - 1, elements, len(elements), 0)

        result = 0
        for element in elements:
            result = result * 10 + element
        print(result)

    def __permutation(self, sequence: int, elements: List[int], length: int, start: int) -> None:
        if 1 == length - start:
            return

        count = self.__get_factorial(length - start - 1)
        index = sequence // count + start
        if index != start:
            auxiliary = elements[index]
            elements[start + 1:index + 1] = elements[start:index]
            elements[start] = auxiliary
        start += 1
        self.__permutation(sequence % count, elements, length, start)

    def __get_factorial(self, value: int) -> int:
        result = 1
        for i in range(2, value + 1):
            result *= i
        return result
