from typing import List

class Problem040:
    def solution(self) -> None:
        target, borders, index = 1000000, [], 0
        while True:
            value = (10 ** index * (9 * index - 1) + 1) // 9
            borders.append(value)
            if value > target:
                break
            index += 1

        result = 1
        while target:
            result *= self.__get_champernowne(target, borders)
            target //= 10
        print(result)

    def __get_champernowne(self, value: int, borders: List[int]) -> int:
        index = self.__get_index(value, borders) - 1
        value -= borders[index] + 1
        digit = 10 ** index + value // (index + 1)
        for i in range(value % (index + 1), index):
            digit //= 10
        return digit % 10

    def __get_index(self, value: int, borders: List[int]) -> int:
        start, end = 0, len(borders) - 1
        while start <= end:
            current = start + ((end - start) >> 1)
            if borders[current] <= value:
                start = current + 1
            else:
                end = current - 1
        return start
