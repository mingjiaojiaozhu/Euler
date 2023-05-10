from typing import List

class Problem052:
    def solution(self) -> None:
        target, pivots, digits, index = 6, [0 for _ in range(10)], [0 for _ in range(10)], 10
        while True:
            self.__get_digits(index, pivots)
            is_same = True
            for i in range(target, 1, -1):
                self.__get_digits(index * i, digits)
                if not self.__check_digits(pivots, digits):
                    is_same = False
                    break
            if is_same:
                print(index)
                return
            index += 1

    def __get_digits(self, value: int, digits: List[int]) -> None:
        digits[:] = [0 for _ in range(10)]
        while value:
            digits[value % 10] += 1
            value //= 10

    def __check_digits(self, pivots: List[int], digits: List[int]) -> bool:
        for pivot, digit in zip(pivots, digits):
            if pivot != digit:
                return False
        return True
