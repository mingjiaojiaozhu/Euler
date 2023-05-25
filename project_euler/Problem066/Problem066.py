import math
from typing import List

class Problem066:
    def solution(self) -> None:
        target, factors, previous, current, auxiliary = 1000, [], self.__Decimal(100, 0), self.__Decimal(100, 0), self.__Decimal(100, 0)
        result, pivot = 0, self.__Decimal(100, 0)
        for i in range(5, target + 1):
            if self.__get_solution(i, factors, previous, current, auxiliary) and self.__is_greater(current, pivot):
                self.__swap_decimal(current, pivot)
                result = i
        print(result)

    def __get_solution(self, value: int, factors: List[int], previous: '__Decimal', current: '__Decimal', auxiliary: '__Decimal') -> bool:
        factors.clear()
        start = self.__get_period(value, factors)
        if not start:
            return False

        self.__set_value(0, previous)
        self.__set_value(1, current)
        self.__get_convergents(previous, current, factors)
        if len(factors) & 1:
            return True

        self.__set_value(1, previous)
        self.__set_value(start, auxiliary)
        self.__get_convergents(previous, auxiliary, factors)
        self.__swap_decimal(previous, current)
        self.__get_product(previous, auxiliary, current)
        self.__get_double(current)
        return True

    def __is_greater(self, current: '__Decimal', pivot: '__Decimal') -> bool:
        if current.length != pivot.length:
            return current.length > pivot.length

        for i in range(current.length - 1, -1, -1):
            if current.value[i] != pivot.value[i]:
                return current.value[i] > pivot.value[i]
        return False

    def __swap_decimal(self, previous: '__Decimal', current: '__Decimal') -> None:
        length = max(previous.length, current.length)
        for i in range(length):
            previous.value[i], current.value[i] = current.value[i], previous.value[i]
        previous.length, current.length = current.length, previous.length

    def __get_period(self, value: int, factors: List[int]) -> int:
        if math.fabs(math.floor(math.sqrt(value) + 0.5) - math.sqrt(value)) < 0.00000001:
            return 0

        initial = int(math.sqrt(value))
        pivot, current, offset, factor = initial << 1, initial, 0, 1
        while current != pivot:
            offset = current * factor - offset
            factor = (value - offset * offset) // factor
            current = (initial + offset) // factor
            factors.append(current)
        factors.pop()
        return initial

    def __set_value(self, value: int, decimal: '__Decimal') -> None:
        decimal.value[:] = [0 for _ in range(100)]
        decimal.value[0], decimal.length = value, 1

    def __get_convergents(self, previous: '__Decimal', current: '__Decimal', factors: List[int]) -> None:
        for factor in factors:
            self.__get_summation(current, factor, previous)
            self.__swap_decimal(previous, current)

    def __get_product(self, multiplicand: '__Decimal', multiplier: '__Decimal', product: '__Decimal'):
        for i in range(multiplicand.length):
            for j in range(multiplier.length):
                value, index = multiplicand.value[i] * multiplier.value[j], i + j
                product.value[index] += value % int(1e5)
                product.value[index + 1] += value // int(1e5)
        product.length = multiplicand.length + multiplier.length - 1
        self.__carry(product)

    def __get_double(self, decimal: '__Decimal') -> None:
        for i in range(decimal.length):
            decimal.value[i] <<= 1
        self.__carry(decimal)

    def __get_summation(self, decimal: '__Decimal', factor: int, summation: '__Decimal') -> None:
        for i in range(decimal.length):
            summation.value[i] += decimal.value[i] * factor
        self.__carry(summation)

    def __carry(self, decimal: '__Decimal') -> None:
        for i in range(decimal.length):
            if decimal.value[i] >= int(1e5):
                decimal.value[i + 1] += decimal.value[i] // int(1e5)
                decimal.value[i] %= int(1e5)
        if decimal.value[decimal.length]:
            decimal.length += 1

    class __Decimal:
        def __init__(self, capacity: int, length: int):
            self.value, self.length = [0 for _ in range(capacity)], length
