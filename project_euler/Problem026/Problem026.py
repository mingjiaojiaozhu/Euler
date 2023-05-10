import math
from typing import List

class Problem026:
    def solution(self) -> None:
        target, remainders, result, pivot = 1000, [], 0, 0
        for i in range(target - 1, 6, -2):
            if self.__is_prime(i):
                count = self.__get_digit(i, remainders)
                if pivot < count:
                    pivot, result = count, i
                if count == i - 1:
                    break
        print(result)

    def __is_prime(self, value: int) -> bool:
        if not (value & 1):
            return 2 == value

        border = int(math.sqrt(value))
        for i in range(3, border + 1, 2):
            if not value % i:
                return False
        return 1 != value

    def __get_digit(self, value: int, remainders: List[int]) -> int:
        remainders.clear()
        remainder = 1
        while True:
            remainders.append(remainder)
            remainder = remainder * 10 % value
            if remainder in remainders:
                return len(remainders) - remainders.index(remainder)
