import math
from typing import List

class Problem077:
    def solution(self) -> None:
        target, primes, result = 5000, [2, 3], 11
        while self.__get_ways(result, primes) <= target:
            result += 1
        print(result)

    def __get_ways(self, target: int, primes: List[int]) -> int:
        index = primes[-1] + 2
        while index <= target:
            if self.__is_prime(index):
                primes.append(index)
            index += 2

        ways = [0 for _ in range(target + 1)]
        ways[0] = 1
        for prime in primes:
            for i in range(prime, target + 1):
                ways[i] += ways[i - prime]
        return ways[target]

    def __is_prime(self, value: int) -> bool:
        if 1 != value % 6 and 5 != value % 6:
            return 2 == value or 3 == value

        border = int(math.sqrt(value))
        for i in range(5, border + 1, 6):
            if not value % i or not value % (i + 2):
                return False
        return 1 != value
