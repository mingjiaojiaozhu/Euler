import math
from typing import List

class Problem051:
    def solution(self) -> None:
        target, digits, steps, auxiliary = 8, [[] for _ in range(3)], [], []
        index = 1111
        while True:
            prime = self.__get_next_prime(index)
            if self.__check_digits(prime, digits) and self.__check_prime_family(prime, target, digits, steps, auxiliary):
                print(prime)
                return
            index = prime + 1

    def __get_next_prime(self, value: int) -> int:
        if not (value & 1):
            value += 1

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
            auxiliary.clear()
            self.__combination(digit, 0, 3, len(digit), steps, auxiliary)
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
        if not (value & 1):
            return 2 == value

        border = int(math.sqrt(value))
        for i in range(3, border + 1, 2):
            if not value % i:
                return False
        return 1 != value

    def __combination(self, digits: List[int], start: int, count: int, length: int, steps: List[int], auxiliary: List[int]) -> None:
        if count == len(auxiliary):
            value = 0
            for digit in auxiliary:
                value += digit
            steps.append(value)
            return

        for i in range(start, length):
            auxiliary.append(int(math.pow(10, digits[i])))
            self.__combination(digits, i + 1, count, length, steps, auxiliary)
            auxiliary.pop()
