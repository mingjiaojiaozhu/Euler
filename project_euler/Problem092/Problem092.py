import math
from typing import List

class Problem092:
    def solution(self) -> None:
        target = 10000000
        border, chains, pivot = 9 * 9 * int(math.log10(target)), set(), 89
        chains.add(pivot)

        squares = [i * i for i in range(10)]
        result = 0
        for i in range(1, border + 1):
            if self.__get_chains(i, chains, pivot, squares):
                result += 1
        for i in range(border + 1, target):
            if self.__square_digits(i, squares) in chains:
                result += 1
        print(result)

    def __get_chains(self, value: int, chains: set[int], pivot: int, squares: List[int]) -> bool:
        if value in chains or pivot == value:
            return True
        if 1 == value:
            return False

        result = self.__get_chains(self.__square_digits(value, squares), chains, pivot, squares)
        if result:
            chains.add(value)
        return result

    def __square_digits(self, value: int, squares: List[int]) -> int:
        result = 0
        while value:
            result += squares[value % 10]
            value //= 10
        return result
