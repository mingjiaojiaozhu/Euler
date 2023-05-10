from typing import List

class Problem047:
    def solution(self) -> None:
        target, length = 4, 200000
        factors = [-1 for _ in range(length)]

        count = 0
        for i in range(2, length + 1):
            if target == self.__get_factors(i, factors, length):
                count += 1
                if target == count:
                    print(i - 3)
                    return
            else:
                count = 0

    def __get_factors(self, value: int, factors: List[int], length: int) -> int:
        if -1 == factors[value - 1]:
            index = value
            while index <= length:
                factors[index - 1] = 1
                index *= value

            for i in range(min(value - 1, length // value), 1, -1):
                factors[value * i - 1] = factors[value - 1] + factors[i - 1]
        else:
            for i in range(min(value - 1, length // value), 1, -1):
                if self.__is_relatively_prime(value, i) and -1 == factors[value * i - 1]:
                    factors[value * i - 1] = factors[value - 1] + factors[i - 1]
        return factors[value - 1]

    def __is_relatively_prime(self, i: int, j: int) -> bool:
        while i % j:
            i, j = j, i % j
        return 1 == j
