import math

class Problem080:
    def solution(self) -> None:
        target = 100
        pivot, result = 10 ** (target + 2), 0
        for i in range(2, target + 1):
            root = math.sqrt(i)
            if abs(math.floor(root + 0.5) - root) > 0.00000001:
                value = self.__get_digits(i, pivot)
                result += self.__get_summation(value // int(1e3))
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
