import math
from typing import List

class Problem037:
    def solution(self) -> None:
        target = 1000000
        length = (target + 1) >> 1
        primes = [True for _ in range(length)]
        primes[0] = False

        border = int(math.sqrt(target))
        for i in range(3, border + 1, 2):
            if primes[i >> 1]:
                for j in range(i * i >> 1, length, i):
                    primes[j] = False

        result = 0
        for i in range(11, target, 2):
            if primes[i >> 1] and self.__check_digits(i) and self.__is_truncatable(i, primes):
                result += i
        print(result)

    def __check_digits(self, value: int) -> bool:
        remainder = value % 10
        if 3 != remainder and 7 != remainder:
            return False

        value //= 10
        while value >= 10:
            remainder = value % 10
            if 1 != remainder and 3 != remainder and 7 != remainder and 9 != remainder:
                return False
            value //= 10
        return 2 == value or 3 == value or 5 == value or 7 == value

    def __is_truncatable(self, value: int, primes: List[bool]) -> bool:
        divisor = 1
        while value // divisor >= 10:
            divisor *= 10

        head, tail = value // 10, value % divisor
        while head and tail:
            if (2 != head and not primes[head >> 1]) or not primes[tail >> 1]:
                return False

            divisor //= 10
            head //= 10
            tail %= divisor
        return True
