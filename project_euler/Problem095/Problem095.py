from typing import List

class Problem095:
    def solution(self) -> None:
        target = 1000000
        divisors = [-1 for _ in range(target)]
        for i in range(2, target + 1):
            self.__get_divisor_summation(i, divisors, target)
        for i in range(1, target):
            divisors[i] -= i + 1

        result, pivot, chains = 0, 0, set()
        for i in range(2, target + 1):
            count = self.__get_chain(i, divisors, chains, target)
            if pivot < count:
                pivot, result = count, target
                for value in chains:
                    if result > value:
                        result = value
        print(result)

    def __get_divisor_summation(self, value: int, divisors: List[int], length: int) -> None:
        if -1 == divisors[value - 1]:
            index, count = value, 1
            while index <= length:
                divisors[index - 1] = (value ** (count + 1) - 1) // (value - 1)
                index *= value
                count += 1

            for i in range(min(value - 1, length // value), 1, -1):
                divisors[value * i - 1] = divisors[value - 1] * divisors[i - 1]
        else:
            for i in range(min(value - 1, length // value), 1, -1):
                if self.__is_relatively_prime(value, i) and -1 == divisors[value * i - 1]:
                    divisors[value * i - 1] = divisors[value - 1] * divisors[i - 1]

    def __get_chain(self, value: int, divisors: List[int], chains: set[int], target: int) -> int:
        chains.clear()
        chains.add(value)

        pivot, count = value, 0
        while True:
            value = divisors[value - 1]
            if pivot == value:
                break
            if 1 == value or value >= target or value in chains:
                return 0

            chains.add(value)
            count += 1
        return count

    def __is_relatively_prime(self, i: int, j: int) -> bool:
        while i % j:
            i, j = j, i % j
        return 1 == j
