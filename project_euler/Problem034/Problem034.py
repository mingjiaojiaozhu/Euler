from typing import List

class Problem034:
    def solution(self) -> None:
        factorials = [0 for _ in range(10000)]
        factorials[0] = 1
        auxiliary = [0 for _ in range(10000)]
        auxiliary[0] = 4
        for i in range(1, 10):
            factorials[i] = factorials[i - 1] * i
            auxiliary[i] = factorials[i] + 3

        result = 0
        for i in range(10, 10000):
            factorials[i] = factorials[i // 10] + factorials[i % 10]
            if i == factorials[i]:
                result += i

        for i in range(10, 100):
            auxiliary[i] = factorials[i] + 2
        for i in range(100, 1000):
            auxiliary[i] = factorials[i] + 1
        auxiliary[1000:10000] = factorials[1000:10000]

        for i in range(6 * factorials[9] + 2, 9999, -1):
            if i == self.__get_factorial_digit(i, factorials, auxiliary):
                result += i
        print(result)

    def __get_factorial_digit(self, value: int, factorials: List[int], auxiliary: List[int]) -> int:
        result = 0
        while value >= 10000:
            result += auxiliary[value % 10000]
            value //= 10000
        result += factorials[value]
        return result
