from typing import List

class Problem014:
    def solution(self) -> None:
        target = 1000000
        chains = [-1 for _ in range(target)]
        chains[0], chains[1] = 1, 2

        for i in range(3, target + 1):
            self.__get_collatz(i, chains, target)

        result, pivot = 0, 0
        for i, chain in enumerate(chains[2:]):
            if pivot < chain:
                pivot, result = chain, i + 3
        print(result)

    def __get_collatz(self, value: int, chains: List[int], length: int) -> int:
        if value <= length and -1 != chains[value - 1]:
            return chains[value - 1]

        if value & 1:
            result = self.__get_collatz(3 * value + 1, chains, length) + 1
        else:
            result = self.__get_collatz(value >> 1, chains, length) + 1
        if value <= length:
            chains[value - 1] = result
        return result
