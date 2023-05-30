import math

class Problem016:
    def solution(self) -> None:
        target = 1000
        value, result = self.__get_power(target), 0
        while value:
            result += value % 10
            value //= 10
        print(result)

    def __get_power(self, value: int) -> int:
        if value < 8:
            return int(math.pow(2, value))

        result = self.__get_power(value >> 1)
        result *= result
        if value & 1:
            result <<= 1
        return result
