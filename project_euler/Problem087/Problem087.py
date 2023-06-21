import math
from typing import List

class Problem087:
    def solution(self) -> None:
        target = 50000000
        primes = [[] for _ in range(3)]
        self.__get_primes(primes, 2, 3)

        borders, index = [int(math.sqrt(target)), int(pow(target, 1 / 3)), int(pow(target, 1 / 4))], 3
        for i in range(2, -1, -1):
            size = i + 1
            while index < borders[i]:
                if self.__is_prime(index):
                    self.__get_primes(primes, index, size)
                index += 2

        summations = set()
        for prime in primes[2]:
            pivot = target - prime
            border = self.__get_index(pivot, primes[1])
            for i in range(border):
                value = primes[1][i]
                end = self.__get_index(pivot - value, primes[0])
                for j in range(end):
                    summations.add(prime + value + primes[0][j])
        print(len(summations))

    def __get_primes(self, primes: List[List[int]], pivot: int, size: int) -> None:
        value = pivot
        for i in range(size):
            value *= pivot
            primes[i].append(value)

    def __is_prime(self, value: int) -> bool:
        if 1 != value % 6 and 5 != value % 6:
            return 2 == value or 3 == value

        border = int(math.sqrt(value))
        for i in range(5, border + 1, 6):
            if not value % i or not value % (i + 2):
                return False
        return 1 != value

    def __get_index(self, value: int, primes: List[int]) -> int:
        start, end = 0, len(primes) - 1
        while start <= end:
            current = start + ((end - start) >> 1)
            if primes[current] <= value:
                start = current + 1
            else:
                end = current - 1
        return start
