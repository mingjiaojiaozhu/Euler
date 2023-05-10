import math
from typing import List

class Problem035:
    def solution(self) -> None:
        target = 1000000
        length = (target + 1) >> 1
        primes = [True for _ in range(length)]
        primes[0] = False

        border = int(math.sqrt(target)) + 1
        for i in range(3, border + 1, 2):
            if primes[i >> 1]:
                for j in range(i * i >> 1, length, i):
                    primes[j] = False

        result = 13
        for i in range(101, target, 2):
            if primes[i >> 1] and self.__check_digits(i) and self.__is_circular(i, primes):
                result += 1
        print(result)

    def __check_digits(self, value: int) -> bool:
        while value:
            remainder = value % 10
            if 1 != remainder and 3 != remainder and 7 != remainder and 9 != remainder:
                return False
            value //= 10
        return True

    def __is_circular(self, value: int, primes: List[bool]) -> bool:
        divisor, length = 1, 1
        while value // divisor >= 10:
            divisor *= 10
            length += 1

        for _ in range(1, length):
            value = (value % 10) * divisor + value // 10
            if not primes[value >> 1]:
                return False
        return True
