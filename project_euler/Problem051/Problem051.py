import math
from typing import List

class Problem051:
    def solution(self) -> None:
        target, digits, steps, auxiliary = 8, [[] for _ in range(3)], [], [0 for _ in range(3)]
        result = 1111
        while True:
            result = self.__get_next_prime(result)
            if self.__check_digits(result, digits) and self.__check_prime_family(result, target, digits, steps, auxiliary):
                print(result)
                return

    def __get_next_prime(self, value: int) -> int:
        if not (value & 1):
            value += 1
        else:
            value += 2

        while not self.__is_prime(value):
            value += 2
        return value

    def __check_digits(self, value: int, digits: List[List[int]]) -> bool:
        for i in range(3):
            digits[i].clear()

        value //= 10
        count = 1
        while value:
            remainder = value % 10
            if not remainder or 1 == remainder or 2 == remainder:
                digits[remainder].append(count)
            value //= 10
            count += 1

        for digit in digits:
            if len(digit) >= 3:
                return True
        return False

    def __check_prime_family(self, pivot: int, target: int, digits: List[List[int]], steps: List[int], auxiliary: List[int]) -> bool:
        is_family = False
        for i, digit in enumerate(digits):
            if len(digit) < 3:
                continue

            steps.clear()
            self.__combination(digit, 0, 3, len(digit), steps, auxiliary, 0)
            for step in steps:
                count, value = 10 - target - i, pivot
                for _ in range(i, 9):
                    value += step
                    if not self.__is_prime(value):
                        count -= 1
                    if count < 0:
                        break
                is_family = not count
        return is_family

    def __is_prime(self, value: int) -> bool:
        if 1 != value % 6 and 5 != value % 6:
            return 2 == value or 3 == value

        border = int(math.sqrt(value))
        for i in range(5, border + 1, 6):
            if not value % i or not value % (i + 2):
                return False
        return 1 != value

    def __combination(self, digits: List[int], start: int, count: int, length: int, steps: List[int], auxiliary: List[int], size: int) -> None:
        if count == size:
            value = 0
            for digit in auxiliary:
                value += digit
            steps.append(value)
            return

        for i in range(start, length):
            auxiliary[size] = 10 ** digits[i]
            size += 1
            self.__combination(digits, i + 1, count, length, steps, auxiliary, size)
            size -= 1
