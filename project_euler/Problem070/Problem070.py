import math
from typing import List

class Problem070:
    def solution(self) -> None:
        target = 10000000
        pivot = int(math.sqrt(target))
        start, end = self.__get_previous_prime(pivot), self.__get_next_prime(pivot)
        primes, pivots, digits, result = [end], [0 for _ in range(10)], [0 for _ in range(10)], 0
        while True:
            for prime in primes:
                self.__get_digits(start * prime, pivots)
                self.__get_digits((start - 1) * (prime - 1), digits)
                if self.__check_digits(pivots, digits):
                    result = start * prime

            end = self.__get_next_prime(primes[-1])
            while start * end < target:
                primes.append(end)
                self.__get_digits(start * end, pivots)
                self.__get_digits((start - 1) * (end - 1), digits)
                if self.__check_digits(pivots, digits):
                    result = start * end
                end = self.__get_next_prime(end)

            if result:
                print(result)
                return
            start = self.__get_previous_prime(start)

    def __get_previous_prime(self, value: int) -> int:
        if not (value & 1):
            value -= 1
        else:
            value -= 2

        while not self.__is_prime(value):
            value -= 2
        return value

    def __get_next_prime(self, value: int) -> int:
        if not (value & 1):
            value += 1
        else:
            value += 2

        while not self.__is_prime(value):
            value += 2
        return value

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

    def __is_prime(self, value: int) -> bool:
        if 1 != value % 6 and 5 != value % 6:
            return 2 == value or 3 == value

        border = int(math.sqrt(value))
        for i in range(5, border + 1, 6):
            if not value % i or not value % (i + 2):
                return False
        return 1 != value
