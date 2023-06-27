from typing import List

class Problem052:
    def solution(self) -> None:
        target, digits, index = 6, [[0 for _ in range(10)] for _ in range(2)], 10
        while True:
            self.__get_digits(index, digits[0])
            is_same = True
            for i in range(target, 1, -1):
                self.__get_digits(index * i, digits[1])
                if not self.__check_digits(digits):
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

    def __check_digits(self, digits: List[List[int]]) -> bool:
        for i in range(10):
            if digits[0][i] != digits[1][i]:
                return False
        return True
