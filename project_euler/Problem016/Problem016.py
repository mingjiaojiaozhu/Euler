import math
from typing import List

class Problem016:
    def solution(self) -> None:
        target = 1000
        length = (target + 4) // 5
        decimal, auxiliary = self.__Decimal(length, 0), [0 for _ in range(length)]
        self.__get_power(target, decimal, auxiliary, length)

        result = 0
        for value in decimal.value[:decimal.length]:
            while value:
                result += value % 10
                value //= 10
        print(result)

    def __get_power(self, value: int, decimal: '__Decimal', auxiliary: List[int], length: int) -> None:
        if value < 8:
            decimal.value[0], decimal.length = int(math.pow(2, value)), 1
            return

        self.__get_power(value >> 1, decimal, auxiliary, length)
        self.__get_square(decimal, auxiliary, length)
        if value & 1:
            self.__get_double(decimal)

    def __get_square(self, decimal: '__Decimal', auxiliary: List[int], length: int) -> None:
        auxiliary[:] = [0 for _ in range(length)]
        for i in range(decimal.length):
            for j in range(decimal.length):
                result, index = decimal.value[i] * decimal.value[j], i + j
                auxiliary[index] += result % int(1e5)
                auxiliary[index + 1] += result // int(1e5)

        decimal.length = (decimal.length << 1) - 1
        for i in range(decimal.length):
            if auxiliary[i] >= int(1e5):
                auxiliary[i + 1] += auxiliary[i] // int(1e5)
                auxiliary[i] %= int(1e5)
        if auxiliary[decimal.length]:
            decimal.length += 1
        decimal.value[:decimal.length] = auxiliary[:decimal.length]

    def __get_double(self, decimal: '__Decimal') -> None:
        for i in range(decimal.length):
            decimal.value[i] <<= 1

        for i in range(decimal.length):
            if decimal.value[i] >= int(1e5):
                decimal.value[i + 1] += decimal.value[i] // int(1e5)
                decimal.value[i] %= int(1e5)
        if decimal.value[decimal.length]:
            decimal.length += 1

    class __Decimal:
        def __init__(self, capacity: int, length: int):
            self.value, self.length = [0 for _ in range(capacity)], length
