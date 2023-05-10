import math
from typing import List

class Problem055:
    def solution(self) -> None:
        target, decimal, auxiliary, result = 10000, self.__Decimal(100, 0), [0 for _ in range(100)], 0
        for i in range(1, target + 1):
            if self.__is_lychrel(i, target, decimal, auxiliary):
                result += 1
        print(result)

    def __is_lychrel(self, value: int, target: int, decimal: '__Decimal', auxiliary: List[int]) -> bool:
        count = 0
        while count < 50:
            if value <= target:
                value += self.__reverse_value(value)
                if self.__is_palindrome(value):
                    return False
            else:
                return self.__is_lychrel_decimal(value, count, decimal, auxiliary)
            count += 1
        return True

    def __reverse_value(self, value: int) -> int:
        result = 0
        while value:
            result = result * 10 + value % 10
            value //= 10
        return result

    def __is_palindrome(self, value: int) -> bool:
        divisor = 1
        while 10 <= value // divisor:
            divisor *= 10

        while value > 1:
            head, tail = value // divisor, value % 10
            if head != tail:
                return False

            value = value % divisor // 10
            divisor //= 100
        return True

    def __is_lychrel_decimal(self, value: int, count: int, decimal: '__Decimal', auxiliary: List[int]) -> bool:
        self.__set_value(value, decimal)
        self.__reverse_decimal(decimal, auxiliary)
        while count < 50:
            self.__get_summation(decimal, auxiliary)
            if self.__is_palindrome_decimal(decimal, auxiliary):
                return False
            count += 1
        return True

    def __set_value(self, value: int, decimal: '__Decimal') -> None:
        decimal.value[:] = [0 for _ in range(100)]
        decimal.length = 0
        while value:
            decimal.value[decimal.length] = value % int(1e5)
            decimal.length += 1
            value //= int(1e5)

    def __reverse_decimal(self, decimal: '__Decimal', auxiliary: List[int]) -> None:
        auxiliary[:] = [0 for _ in range(100)]
        index, count = 0, 0
        for i in range(decimal.length - 1, -1, -1):
            value, divisor = decimal.value[i], int(1e5) // 10
            if i == decimal.length - 1:
                while not value // divisor:
                    divisor //= 10
            while divisor:
                auxiliary[index] += (value // divisor) * int(math.pow(10, count))
                value %= divisor
                divisor //= 10
                count += 1
                if 5 == count:
                    index += 1
                    count = 0

    def __get_summation(self, decimal: '__Decimal', auxiliary: List[int]) -> None:
        for i in range(decimal.length):
            decimal.value[i] += auxiliary[i]

        for i in range(decimal.length):
            if decimal.value[i] >= int(1e5):
                decimal.value[i + 1] += decimal.value[i] // int(1e5)
                decimal.value[i] %= int(1e5)
        if decimal.value[decimal.length]:
            decimal.length += 1

    def __is_palindrome_decimal(self, decimal: '__Decimal', auxiliary: List[int]) -> bool:
        self.__reverse_decimal(decimal, auxiliary)
        for i in range(decimal.length):
            if decimal.value[i] != auxiliary[i]:
                return False
        return True

    class __Decimal:
        def __init__(self, capacity: int, length: int):
            self.value, self.length = [0 for _ in range(capacity)], length
