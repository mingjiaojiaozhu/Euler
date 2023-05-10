import math
from typing import List

class Problem021:
    def solution(self) -> None:
        target = 10000
        divisors = [-1 for _ in range(target)]
        for i in range(2, target + 1):
            self.__get_divisor_summation(i, divisors, target)
        for i in range(1, target):
            divisors[i] -= i + 1

        result = 0
        for i in range(2, target + 1):
            divisor = divisors[i - 1]
            if divisor > i and divisor <= target and divisors[divisor - 1] == i:
                result += i + divisor
        print(result)

    def __get_divisor_summation(self, value: int, divisors: List[int], length: int) -> None:
        if -1 == divisors[value - 1]:
            index, count = value, 1
            while index <= length:
                divisors[index - 1] = (int(math.pow(value, count + 1)) - 1) // (value - 1)
                index *= value
                count += 1

            for i in range(min(value - 1, length // value), 1, -1):
                divisors[value * i - 1] = divisors[value - 1] * divisors[i - 1]
        else:
            for i in range(min(value - 1, length // value), 1, -1):
                if self.__is_relatively_prime(value, i) and -1 == divisors[value * i - 1]:
                    divisors[value * i - 1] = divisors[value - 1] * divisors[i - 1]

    def __is_relatively_prime(self, i: int, j: int) -> bool:
        while i % j:
            i, j = j, i % j
        return 1 == j
