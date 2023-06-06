import math
from typing import List

class Problem060:
    def solution(self) -> None:
        target, primes = 5, []
        for i in range(3, 10000, 2):
            if self.__is_prime(i):
                primes.append(i)

        length = len(primes)
        edges = [[0 for _ in range(length)] for _ in range(length)]
        for i in range(1, length):
            value = primes[i]
            if self.__check_prime(self.__merge(3, value), primes) and self.__check_prime(self.__merge(value, 3), primes):
                edges[0][i], edges[i][0] = 1, 1
        for i in range(1, length):
            pivot = primes[i]
            for j in range(i + 1, length):
                value = primes[j]
                if pivot % 3 == value % 3 and self.__check_prime(self.__merge(pivot, value), primes) and self.__check_prime(self.__merge(value, pivot), primes):
                    edges[i][j], edges[j][i] = 1, 1

        cliques, indexes = [], []
        for i in range(length):
            indexes.append(i)
        self.__search(primes, edges, cliques, indexes, target)

    def __is_prime(self, value: int) -> bool:
        if 1 != value % 6 and 5 != value % 6:
            return 2 == value or 3 == value

        border = int(math.sqrt(value))
        for i in range(5, border + 1, 6):
            if not value % i or not value % (i + 2):
                return False
        return 1 != value

    def __check_prime(self, value: int, primes: List[int]) -> bool:
        if value < 10000:
            start, end = 0, len(primes) - 1
            while start <= end:
                current = start + ((end - start) >> 1)
                prime = primes[current]
                if prime == value:
                    return True

                if prime < value:
                    start = current + 1
                else:
                    end = current - 1
            return False

        border, start, end = int(math.sqrt(value)), 0, len(primes) - 1
        while start <= end:
            current = start + ((end - start) >> 1)
            if primes[current] <= border:
                start = current + 1
            else:
                end = current - 1

        for prime in primes[:start]:
            if not value % prime:
                return False
        return True

    def __merge(self, head: int, tail: int) -> int:
        return head * 10 ** (int(math.log10(tail)) + 1) + tail

    def __search(self, primes: List[int], edges: List[List[int]], cliques: List[int], indexes: List[int], target: int) -> None:
        if not indexes:
            if len(cliques) == target:
                result = 0
                for index in cliques:
                    result += primes[index]
                print(result)
            return

        start = indexes[0]
        for i in range(len(indexes) - 1, -1, -1):
            index = indexes[i]
            if not edges[start][index]:
                cliques.append(index)
                self.__search(primes, edges, cliques, self.__get_adjacents(edges, indexes, index), target)
                cliques.pop()
                indexes.remove(index)

    def __get_adjacents(self, edges: List[List[int]], indexes: List[int], start: int) -> List[int]:
        auxiliary = []
        for index in indexes:
            if edges[start][index]:
                auxiliary.append(index)
        return auxiliary
