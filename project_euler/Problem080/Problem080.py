import math

class Problem080:
    def solution(self) -> None:
        target = 100
        pivot, divisor, result = 10 ** (target + 2), 10 ** 3, 0
        for i in range(2, target + 1):
            if abs(math.floor(math.sqrt(i) + 0.5) - math.sqrt(i)) > 0.00000001:
                value = self.__get_digits(i, pivot)
                result += self.__get_summation(value // divisor)
        print(result)

    def __get_digits(self, value: int, pivot: int) -> int:
        current, auxiliary = 5, value * 5
        while current < pivot:
            if current <= auxiliary:
                current, auxiliary = current + 10, auxiliary - current
            else:
                remainder = current % 10
                current, auxiliary = (current - remainder) * 10 + remainder, auxiliary * 100
        return current

    def __get_summation(self, value: int) -> int:
        result = 0
        while value:
            result += value % 10
            value //= 10
        return result
